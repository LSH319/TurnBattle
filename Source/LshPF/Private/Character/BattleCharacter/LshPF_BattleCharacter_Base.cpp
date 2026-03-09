// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"

#include "LshPF_GameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Component/LshPF_BattleComponent.h"
#include "Controllers/LshPF_PlayerController_Battle.h"
#include "Engine/AssetManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameModes/LshPF_BattleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

ALshPF_BattleCharacter_Base::ALshPF_BattleCharacter_Base()
{
	LshPF_BattleComponent = CreateDefaultSubobject<ULshPF_BattleComponent>("BattleComponent");
	
	FrontCameraBoom = CreateDefaultSubobject<USpringArmComponent>("FrontCameraBoom");
	FrontCameraBoom->SetupAttachment(RootComponent);
	
	FrontCameraComponent = CreateDefaultSubobject<UCameraComponent>("FrontCameraComponent");
	FrontCameraComponent->SetupAttachment(FrontCameraBoom);
	FrontCameraComponent->SetAutoActivate(false);
	FrontCameraComponent->SetActive(false);
	
	BackCameraBoom = CreateDefaultSubobject<USpringArmComponent>("BackCameraBoom");
	BackCameraBoom->SetupAttachment(RootComponent);
	
	BackCameraComponent = CreateDefaultSubobject<UCameraComponent>("BackCameraComponent");
	BackCameraComponent->SetupAttachment(BackCameraBoom);
	BackCameraComponent->SetAutoActivate(false);
	BackCameraComponent->SetActive(true);
	
	TargetingParticle = CreateDefaultSubobject<UParticleSystemComponent>("TargetingParticle");
	TargetingParticle->SetupAttachment(RootComponent);
	TargetingParticle->bAutoActivate = false;

	GuardParticle = CreateDefaultSubobject<UParticleSystemComponent>("GuardParticle");
	GuardParticle->SetupAttachment(RootComponent);
	GuardParticle->bAutoActivate = false;
}

ULshPF_BattleComponent* ALshPF_BattleCharacter_Base::GetBattleComponent() const
{
	return LshPF_BattleComponent;
}

void ALshPF_BattleCharacter_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ToggleTargeting(false);
	ToggleGuard(false);
	
	//BaseHealth 와 BaseMana 를 Max 값으로 설정
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseHealth,LshPF_BattleComponent->GetAttribute(EAttributeType::BaseMaxHealth));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMana,LshPF_BattleComponent->GetAttribute(EAttributeType::BaseMaxMana));

	//Current 값을 Base 값과 동기화
	LshPF_BattleComponent->SetAllCurrentAttributeToBaseAttribute();
}

void ALshPF_BattleCharacter_Base::BeginPlay()
{
	IsBeginPlay = true;
	Super::BeginPlay();

	if (IsCharacterReady())
	{
		//캐릭터의 준비 완료 시 GM 으로 전송
		GetBattleGameMode()->CharacterReady(this);
	}
}

int32 ALshPF_BattleCharacter_Base::GetAttribute(EAttributeType AttributeType)
{
	return LshPF_BattleComponent->GetAttribute(AttributeType);
}

void ALshPF_BattleCharacter_Base::SetAttribute(EAttributeType AttributeType, int32 NewAttribute)
{
	LshPF_BattleComponent->SetAttribute(AttributeType, NewAttribute);
}

void ALshPF_BattleCharacter_Base::TurnStart()
{
	IsCharacterHaveTurn = true;
	ToggleGuard(false);
	OnTurnStartDelegate.Broadcast();
}

void ALshPF_BattleCharacter_Base::TurnEnd()
{
	IsCharacterHaveTurn = false;
	OnTurnEndDelegate.Broadcast();
	GetBattleGameMode()->TargetTurnEnd(this);
}

bool ALshPF_BattleCharacter_Base::IsPlayerCharacter()
{
	return false;
}

ULshPF_BattleComponent* ALshPF_BattleCharacter_Base::GetBattleComponent()
{
	return LshPF_BattleComponent;
}

void ALshPF_BattleCharacter_Base::ToggleTargeting(bool IsActive)
{
	if (IsActive)
	{
		TargetingParticle->Activate(true);
	}
	else
	{
		TargetingParticle->DeactivateImmediate();
		TargetingParticle->ForceReset();
	}
}

void ALshPF_BattleCharacter_Base::ToggleGuard(bool IsActive)
{
	if (IsActive)
	{
		LshPF_BattleComponent->SetIsGuard(true);
		GuardParticle->Activate(true);

		//Guard 실행 시 1초 후 턴 종료 호출
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			FTimerDelegate::CreateLambda([this]()
				{
					TurnEnd();
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				}),
			1.f,
			false);
	}
	else
	{
		LshPF_BattleComponent->SetIsGuard(false);
		GuardParticle->DeactivateImmediate();
		GuardParticle->ForceReset();
	}
}

void ALshPF_BattleCharacter_Base::PlayAnimMontageByTag(FGameplayTag AnimMontageTag)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		SetViewTargetSelf(true);
		UAnimMontage* CachedMontage = CharacterMontageMap.FindChecked(AnimMontageTag);
		if (AnimInstance->Montage_Play(CachedMontage) > 0.f)
		{
			FOnMontageEnded EndDelegate;

			if (AnimMontageTag == LshPF_GameplayTags::LshPF_AnimMontage_Attack ||
				AnimMontageTag == LshPF_GameplayTags::LshPF_AnimMontage_Skill)
			{
				EndDelegate.BindUObject(this, &ALshPF_BattleCharacter_Base::OnTriggerMontageEnded);
			}
			else if (AnimMontageTag == LshPF_GameplayTags::LshPF_AnimMontage_HitReact||
					 AnimMontageTag == LshPF_GameplayTags::LshPF_AnimMontage_Death)
			{
				EndDelegate.BindUObject(this, &ALshPF_BattleCharacter_Base::OnReactMontageEnded);
			}
			
			AnimInstance->Montage_SetEndDelegate(EndDelegate, CachedMontage);
		}
	}
}

void ALshPF_BattleCharacter_Base::SetCharacterKey(FName NewCharacterKey)
{
	CharacterKey = NewCharacterKey;
}

void ALshPF_BattleCharacter_Base::SetCharacterName(const FText& NewCharacterName)
{
	LshPF_BattleComponent->SetCharacterName(NewCharacterName);
}

void ALshPF_BattleCharacter_Base::AddSoftAnimMontageMap(TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> MontageMap)
{
	int32 MontageCount = MontageMap.Num();
	for (TTuple<FGameplayTag, TSoftObjectPtr<UAnimMontage>> Montage : MontageMap)
	{
		//시작 전 Montage 로드 및 추가
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
        	Montage.Value.ToSoftObjectPath(),
        	FStreamableDelegate::CreateLambda(
        		[this, Montage, MontageCount]()
        		{
        			CharacterMontageMap.Add(Montage.Key, Montage.Value.Get());
        			if (CharacterMontageMap.Num() >= MontageCount)
        			{
        				IsMontageReady = true;
        				if (IsCharacterReady())
        				{
        					//캐릭터의 준비 완료 시 GM 으로 전송
        					GetBattleGameMode()->CharacterReady(this);
        				}
        			}
        		})
        	);
	}
	
}

void ALshPF_BattleCharacter_Base::SetCharacterOrderPriority(int32 NewCharacterOrderPriority)
{
	CharacterOrderPriority = NewCharacterOrderPriority;
}

int32 ALshPF_BattleCharacter_Base::GetCharacterOrderPriority() const
{
	return CharacterOrderPriority;
}

FVector ALshPF_BattleCharacter_Base::GetBattleCharacterLocation()
{
	return GetActorLocation();
}

void ALshPF_BattleCharacter_Base::SetLookAtRotation(FVector TargetLocation)
{
	FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetBattleCharacterLocation(), TargetLocation);
	SetActorRotation(LookAtRotator);
}

void ALshPF_BattleCharacter_Base::CharacterDeath()
{
	IsCharacterDeath = true;
	ToggleGuard(false);
	GetBattleGameMode()->CharacterDeath(this);
}

ALshPF_BattleGameMode* ALshPF_BattleCharacter_Base::GetBattleGameMode()
{
	if (!CachedBattleGameMode)
	{
		CachedBattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	}
	return CachedBattleGameMode;
}

ALshPF_PlayerController_Battle* ALshPF_BattleCharacter_Base::GetBattlePlayerController()
{
	if (!CachedPlayerController)
	{
		CachedPlayerController = Cast<ALshPF_PlayerController_Battle>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
	return CachedPlayerController;;
}

bool ALshPF_BattleCharacter_Base::IsCharacterReady()
{
	//Montage 로드 및 저장 완료 && 캐릭터의 BeginPlay 호출 이후 체크
	return IsMontageReady && IsBeginPlay;
}

void ALshPF_BattleCharacter_Base::SetViewTargetSelf(bool TargetIsFrontCamera)
{
	if (TargetIsFrontCamera)
	{
		FrontCameraComponent->SetActive(true);
		BackCameraComponent->SetActive(false);
	}
	else
	{
		FrontCameraComponent->SetActive(false);
		BackCameraComponent->SetActive(true);
	}
	GetBattlePlayerController()->SetViewTarget(this);
}

void ALshPF_BattleCharacter_Base::OnTriggerMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	TArray<ULshPF_BattleComponent*> TargetList;
	for (ILshPF_BattleInterface* TargetInterface : GetTargetInterfaceList())
	{
		TargetList.Add(TargetInterface->GetBattleComponent());
	}
	GetBattleGameMode()->SetTriggerCharacter(this);
	FBattleAttributeModifier BattleAttributeModifier = GetTargetModifier();

	for (ULshPF_BattleComponent* TargetBattleComponent : TargetList)
	{
		if (TargetBattleComponent)
		{
			//ApplyDamageToTarget 호출 시 Target 의 TakeDamageFromCursor 호출,
			//Target 의 TakeDamageFromCursor 에서 Target 의 HitReact 재생
			//Target 의 HitReact 종료 시 ReactMontageEndedCallback 호출
			GetBattleComponent()->ApplyDamageToTarget(
				TargetBattleComponent,
				GetBattleComponent(),
				BattleAttributeModifier);
		}
	}
}

void ALshPF_BattleCharacter_Base::OnReactMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (GetBattleComponent()->IsDead())
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Pause(Montage);
		}
	}
	
	GetBattleGameMode()->ReactMontageEndedEvent.ExecuteIfBound();
}

TArray<ILshPF_BattleInterface*> ALshPF_BattleCharacter_Base::GetTargetInterfaceList()
{
	return GetBattlePlayerController()->GetTargetList();
}

FBattleAttributeModifier ALshPF_BattleCharacter_Base::GetTargetModifier()
{
	return GetBattlePlayerController()->GetTargetModifier();
}
