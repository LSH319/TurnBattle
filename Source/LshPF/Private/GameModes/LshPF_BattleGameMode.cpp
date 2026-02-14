// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LshPF_BattleGameMode.h"

#include "LshPF_GameInstance.h"
#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"
#include "Character/BattleCharacter/LshPF_EnemyBattleCharacter.h"
#include "Data/EnemyMeshInfo.h"
#include "Engine/AssetManager.h"
#include "Interface/LshPF_BattleInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LshPF_UISubsystem.h"

void ALshPF_BattleGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Status UI 준비 완료시 CallBack 등록
	StatusUIReady.AddDynamic(this, &ThisClass::StatusUIReadyCallBack);
}

void ALshPF_BattleGameMode::BeginPlay()
{
	Super::BeginPlay();

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
		GrantTurn();
	}
}

ILshPF_BattleInterface* ALshPF_BattleGameMode::GetRecentOwingTurnCharacter() const
{
	return RecentOwingTurnCharacter;
}

ILshPF_BattleInterface* ALshPF_BattleGameMode::GetEnemyCharacterByIndex(int Index) const
{
	if (EnemyCharacterList.IsEmpty())
	{
		return nullptr;
	}
	//Index 가 유효 범위를 벗어난 경우 조정
	Index = FMath::Clamp(Index, 0, EnemyCharacterList.Num() - 1);
	return EnemyCharacterList[Index];
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
		GrantTurn();
	}
}

bool ALshPF_BattleGameMode::IsGameReady() const
{
	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	if (
		/*todo : 테스트용 TestEnemyCount 사용중, 테스트 후 변경
		GameInstance->GetAllCharacterCount() == TurnTable.Num() &&*/
		GameInstance->GetPlayerCharacterCount() + TestEnemyCount == TurnTable.Num() &&
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
	checkf(!FoundPoints.IsEmpty(), TEXT("SpawnPointActorTag Is Error"));

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
	for (int i = 0; i < EnemyCount; i++)
	{
		FTransform EnemyTransform;
		EnemyTransform.SetLocation(SpawnPoint);
		EnemyTransform.SetRotation(EnemySpawnQuat);

		//Spawn 전 설정을 위해 SpawnActorDeferred 사용
		ALshPF_BattleCharacter_Base* SpawnedActor = GetWorld()->SpawnActorDeferred<ALshPF_BattleCharacter_Base>(
			EnemyMeshInfo->EnemyBattleCharacterBaseClass,
			EnemyTransform
		);

		//Spawn 시 무작위 생성을 위한 코드
		TArray<FName> EnemyKeyNames;
		EnemyMeshInfo->EnemyMeshInfoMap.GetKeys(EnemyKeyNames);
		int32 RandomIndex = FMath::RandRange(0, EnemyKeyNames.Num() - 1);
		FName RandomKey = EnemyKeyNames[RandomIndex];
		SpawnedActor->SetCharacterKeyName(RandomKey);
		
		//FinishSpawning 전 필요한 값 설정
		FEnemyMeshData EnemyMeshData = EnemyMeshInfo->GetEnemyMeshInfoByEnemyKeyName(RandomKey);

		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			EnemyMeshData.SkeletalMesh.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnedActor, EnemyMeshData, EnemyTransform]
				{
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
