// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LshPF_BattleGameMode.h"

#include "LshPF_GameInstance.h"
#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"
#include "Character/BattleCharacter/LshPF_EnemyBattleCharacter.h"
#include "Character/BattleCharacter/LshPF_PlayerBattleCharacter.h"
#include "Component/LshPF_BattleComponent.h"
#include "Data/EnemyMeshInfo.h"
#include "Data/PlayerCharacterInfo.h"
#include "Engine/AssetManager.h"
#include "Interface/LshPF_BattleInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LshPF_UISubsystem.h"

void ALshPF_BattleGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Status UI 준비 완료시 CallBack 등록
	StatusUIReady.AddDynamic(this, &ThisClass::StatusUIReadyCallBack);

	TriggerMontageEndedEvent.BindUObject(this, &ThisClass::TriggerMontageEndedCallback);
	ReactMontageEndedEvent.BindUObject(this, &ThisClass::ReactMontageEndedCallback);
}

void ALshPF_BattleGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPlayerCharacters();
	SpawnEnemies();
}

void ALshPF_BattleGameMode::CharacterReady(ILshPF_BattleInterface* RequestBattleInterface)
{
	if (RequestBattleInterface->IsPlayerCharacter())
	{
		//Player Character 리스트 에 추가
		PlayerCharacterList.Add(RequestBattleInterface);
		
		if (IsStatusUIReady)
		{
			//Status UI 가 준비된 경우, Subsystem Delegate 를 통해 UI에 추가되도록 Broadcast
			if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
			{
				UISubsystem->OnBattleComponentDelegate.Broadcast(RequestBattleInterface->GetBattleComponent());
			}
		}
		else
		{
			//Status UI 가 준비되지 않은 경우 Queue 에 삽입하여 준비 완료 후 사용
			WaitingRegisterComponents.Enqueue(RequestBattleInterface->GetBattleComponent());
		}
	}
	else
	{
		//Enemy Character 리스트 에 추가
		EnemyCharacterList.Add(RequestBattleInterface);

		//todo : 테스트 완료 후 제거
		//Test 를 위한 추가
		if (IsStatusUIReady)
		{
			if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
			{
				UISubsystem->OnBattleComponentDelegate.Broadcast(RequestBattleInterface->GetBattleComponent());
			}
		}
		else
		{
			WaitingRegisterComponents.Enqueue(RequestBattleInterface->GetBattleComponent());
		}
	}

	RequestAddTurnTable(RequestBattleInterface);
}

void ALshPF_BattleGameMode::CharacterDeath(ILshPF_BattleInterface* RemoveTarget)
{
	//TurnTable 에서 제거
	TurnTable.RemoveAll([RemoveTarget](const FTurnTableData& Data)
	{
		return Data.TargetCharacter == RemoveTarget;
	});

	//CharacterList 에서 제거
	if (RemoveTarget->IsPlayerCharacter())
	{
		PlayerCharacterList.Remove(RemoveTarget);
	}
	else
	{
		EnemyCharacterList.Remove(RemoveTarget);
	}
}

void ALshPF_BattleGameMode::RequestAddTurnTable(ILshPF_BattleInterface* RequestBattleInterface)
{
 	int32 CharacterSpeed = RequestBattleInterface->GetAttribute(EAttributeType::CurrentSpeed);
	float RequireTime = GlobalTimer + (TurnStartTP / CharacterSpeed);
	FTurnTableData TurnTableData(RequireTime, RequestBattleInterface);

	TurnTable.Add(TurnTableData);

	SortTurnTable();
}

void ALshPF_BattleGameMode::TargetTurnEnd(ILshPF_BattleInterface* RequestBattleInterface)
{
	RequestAddTurnTable(RequestBattleInterface);
	GrantTurn();
}

FEnemyAttribute* ALshPF_BattleGameMode::GetEnemyAttributeByKeyName(FName EnemyKeyName) const
{
	FEnemyAttribute* FindEnemyAttribute = EnemyAttributeData->FindRow<FEnemyAttribute>(EnemyKeyName, FString("EnemyKeyName Is Error"));
	checkf(FindEnemyAttribute, TEXT("EnemyKeyName is Error At EnemyAttributeData"));

	return FindEnemyAttribute;
}

void ALshPF_BattleGameMode::SetUIReady(bool NewIsUIReady)
{
	IsUIReady = NewIsUIReady;

	if (IsGameReady())
	{
		//준비 완료시 게임 시작
		SortEnemyList();
		GrantTurn();
	}
}

ILshPF_BattleInterface* ALshPF_BattleGameMode::GetRecentOwingTurnCharacter() const
{
	return RecentOwingTurnCharacter;
}

ILshPF_BattleInterface* ALshPF_BattleGameMode::GetEnemyCharacterByIndex(int32& Index) const
{
	if (EnemyCharacterList.IsEmpty())
	{
		return nullptr;
	}
	//Index 가 유효 범위를 벗어난 경우 조정
	Index = FMath::Clamp(Index, 0, EnemyCharacterList.Num() - 1);
	return EnemyCharacterList[Index];
}

ILshPF_BattleInterface* ALshPF_BattleGameMode::GetPlayerCharacterByIndex(int32& Index) const
{
	if (PlayerCharacterList.IsEmpty())
	{
		return nullptr;
	}
	//Index 가 유효 범위를 벗어난 경우 조정
	Index = FMath::Clamp(Index, 0, PlayerCharacterList.Num() - 1);
	return PlayerCharacterList[Index];
}

TArray<ILshPF_BattleInterface*> ALshPF_BattleGameMode::GetEnemyCharacters() const
{
	return EnemyCharacterList;
}

TArray<ILshPF_BattleInterface*> ALshPF_BattleGameMode::GetPlayerCharacters() const
{
	return PlayerCharacterList;
}

void ALshPF_BattleGameMode::SortTurnTable()
{
	TurnTable.Sort([](
		const FTurnTableData& A, const FTurnTableData& B)
		{
			return A.RequireTime < B.RequireTime;
		});

	if (IsGameReady())
	{
		//준비 완료시 게임 시작
		SortEnemyList();
		GrantTurn();
	}
}

void ALshPF_BattleGameMode::SortEnemyList()
{
	//Spawn 순서에 따라 List 정렬
	//Asset 로드에 따라 순서가 달라질 수 있어 1회 정렬 수행
	EnemyCharacterList.Sort([](
		const ILshPF_BattleInterface& A, const ILshPF_BattleInterface& B)
		{
			return A.GetCharacterOrderPriority() < B.GetCharacterOrderPriority();
		});
}

bool ALshPF_BattleGameMode::IsGameReady() const
{
	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	if (
		/*todo : 테스트용 TestEnemyCount 사용중, 테스트 후 변경
		GameInstance->GetAllCharacterCount() == TurnTable.Num() &&*/
		GameInstance->GetPlayerCharacterKeyNames().Num() + TestEnemyCount == TurnTable.Num() &&
		!IsTurnGranted &&
		IsUIReady)
	{
		return true;
	}
	return false;
}

void ALshPF_BattleGameMode::GrantTurn()
{
	IsTurnGranted = true;
	RecentOwingTurnCharacter = TurnTable[0].TargetCharacter;
	TurnTable[0].TargetCharacter->TurnStart();
	GlobalTimer = TurnTable[0].RequireTime;

	TurnTable.RemoveAt(0);
}

void ALshPF_BattleGameMode::SpawnEnemies()
{
	TArray<AActor*> FoundPoints;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), EnemySpawnPointActorTag, FoundPoints);
	checkf(!FoundPoints.IsEmpty(), TEXT("EnemySpawnPointActorTag Is Error"));
	FVector SpawnPoint = FoundPoints[0]->GetActorLocation();

	/*todo : 테스트용 TestEnemyCount 사용중, 테스트 후 변경
	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	int32 EnemyCount = GameInstance->GetEnemyCharacterCount();*/
	int32 EnemyCount = TestEnemyCount;

	//Enemy Spawn 시 시작지점 계산
	SpawnPoint.Y = SpawnPoint.Y - (CharacterInterval * (EnemyCount/2));
	if (EnemyCount % 2 == 0)
	{
		SpawnPoint.Y = SpawnPoint.Y + (CharacterInterval * 0.5);
	}

	//Enemy 숫자만큼 Spawn 실행
	for (int Index = 0; Index < EnemyCount; Index++)
	{
		FTransform EnemyTransform;
		EnemyTransform.SetLocation(SpawnPoint);
		EnemyTransform.SetRotation(EnemySpawnQuat);
		
		//Spawn 시 무작위 생성을 위한 코드
		TArray<FName> EnemyKeyNames;
		EnemyMeshInfo->EnemyMeshInfoMap.GetKeys(EnemyKeyNames);
		int32 RandomIndex = FMath::RandRange(0, EnemyKeyNames.Num() - 1);
		FName RandomKey = EnemyKeyNames[RandomIndex];

		//Spawn 시 사용할 Mesh 데이터
		FEnemyMeshData EnemyMeshData = EnemyMeshInfo->GetEnemyMeshInfoByKeyName(RandomKey);
		
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			EnemyMeshData.SkeletalMesh.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[this, EnemyMeshData, EnemyTransform, RandomKey, Index]
				{
					//Spawn 전 설정을 위해 SpawnActorDeferred 사용
					ALshPF_BattleCharacter_Base* SpawnedActor = GetWorld()->SpawnActorDeferred<ALshPF_BattleCharacter_Base>(
						EnemyMeshInfo->EnemyBattleCharacterBaseClass,
						EnemyTransform
					);
					
					//FinishSpawning 전 필요한 값 설정
					SpawnedActor->SetCharacterKey(RandomKey);
					SpawnedActor->SetCharacterName(EnemyMeshData.CharacterName);
					SpawnedActor->AddSoftAnimMontageMap(EnemyMeshData.EnemyMontageMap);
					//몇번째 Spawn 인지 추가해 List Sort에 활용
					SpawnedActor->SetCharacterOrderPriority(Index);
					
					//Enemy 의 매쉬관련 설정
					SpawnedActor->GetMesh()->SetSkeletalMesh(EnemyMeshData.SkeletalMesh.Get());
					SpawnedActor->GetMesh()->SetAnimInstanceClass(EnemyMeshData.AnimClass);
					SpawnedActor->FinishSpawning(EnemyTransform);
				})
		);

		//Spawn 위치를 Interval 만큼 이동
		SpawnPoint.Y = SpawnPoint.Y + CharacterInterval;
	}
}

void ALshPF_BattleGameMode::SpawnPlayerCharacters()
{
	TArray<AActor*> FoundPoints;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), PlayerSpawnPointActorTag, FoundPoints);
	checkf(!FoundPoints.IsEmpty(), TEXT("PlayerSpawnPointActorTag Is Error"));
	FVector SpawnPoint = FoundPoints[0]->GetActorLocation();
	
	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	TArray<FName> PlayerCharacterKeyNames = GameInstance->GetPlayerCharacterKeyNames();
	int32 PlayerCharacterCount = PlayerCharacterKeyNames.Num();
	
	//Spawn 시 시작지점 계산
	SpawnPoint.Y = SpawnPoint.Y - (CharacterInterval * (PlayerCharacterCount/2));
	if (PlayerCharacterCount % 2 == 0)
	{
		SpawnPoint.Y = SpawnPoint.Y + (CharacterInterval * 0.5);
	}

	//Count 숫자만큼 Spawn 실행
	for (FName PlayerCharacterKeyName : PlayerCharacterKeyNames)
	{
		FTransform PlayerTransform;
		PlayerTransform.SetLocation(SpawnPoint);
		PlayerTransform.SetRotation(PlayerSpawnQuat);

		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			PlayerCharacterInfo->GetPlayerCharacterClassByKeyName(PlayerCharacterKeyName).ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, PlayerCharacterKeyName, PlayerTransform]
			{
				ALshPF_BattleCharacter_Base* SpawnedActor = GetWorld()->SpawnActorDeferred<ALshPF_BattleCharacter_Base>(
					PlayerCharacterInfo->GetPlayerCharacterClassByKeyName(PlayerCharacterKeyName).Get(),
					PlayerTransform
				);
				
				//FinishSpawning 전 필요한 값 설정
				SpawnedActor->SetCharacterKey(PlayerCharacterKeyName);
				SpawnedActor->FinishSpawning(PlayerTransform);
			})
		);
		
		//Spawn 위치를 Interval 만큼 이동
		SpawnPoint.Y = SpawnPoint.Y + CharacterInterval;
	}
}

void ALshPF_BattleGameMode::TriggerMontageEndedCallback(TArray<ULshPF_BattleComponent*> TargetBattleComponents, FBattleAttributeModifier BattleAttributeModifier)
{
	ILshPF_BattleInterface* TurnCharacter = GetRecentOwingTurnCharacter();

	//TargetBattleInterfaces 가 empty 인지 확인
	if (TurnCharacter && !TargetBattleComponents.IsEmpty())
	{
		for (ULshPF_BattleComponent* TargetBattleComponent : TargetBattleComponents)
		{
			if (TargetBattleComponent)
			{
				//ApplyDamageToTarget 호출 시 Target 의 TakeDamageFromCursor 호출,
				//Target 의 TakeDamageFromCursor 에서 Target 의 HitReact 재생
				//Target 의 HitReact 종료 시 ReactMontageEndedCallback 호출
				TurnCharacter->GetBattleComponent()->ApplyDamageToTarget(
					TargetBattleComponent,
					TurnCharacter->GetBattleComponent(),
					BattleAttributeModifier);
			}
		}
	}
	else
	{
		//TargetBattleInterfaces 가 empty인 경우 즉시 턴 종료
		GetRecentOwingTurnCharacter()->TurnEnd();
	}
}

void ALshPF_BattleGameMode::ReactMontageEndedCallback()
{
	GetRecentOwingTurnCharacter()->TurnEnd();
}

void ALshPF_BattleGameMode::StatusUIReadyCallBack()
{
	//Status UI 준비여부 변경
	IsStatusUIReady = true;

	//Queue 에 삽입되어 있던 요소들을 전부 사용할때까지
	while(!WaitingRegisterComponents.IsEmpty())
	{
		ULshPF_BattleComponent* BattleComponent;
		WaitingRegisterComponents.Dequeue(BattleComponent);
		if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
		{
			//UI Subsystem 의 Delegate 를 통해 Broadcast 
			UISubsystem->OnBattleComponentDelegate.Broadcast(BattleComponent);
		}
	}
}
