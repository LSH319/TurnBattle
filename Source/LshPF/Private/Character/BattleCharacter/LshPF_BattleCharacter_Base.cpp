// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"

#include "LshPF_GameplayTags.h"
#include "Component/LshPF_BattleComponent.h"
#include "Engine/AssetManager.h"
#include "GameModes/LshPF_BattleGameMode.h"
#include "Particles/ParticleSystemComponent.h"

ALshPF_BattleCharacter_Base::ALshPF_BattleCharacter_Base()
{
	LshPF_BattleComponent = CreateDefaultSubobject<ULshPF_BattleComponent>("BattleComponent");

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
	ToggleGuard(false);
	OnTurnStartDelegate.Broadcast();
}

void ALshPF_BattleCharacter_Base::TurnEnd()
{
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
	PlayAnimMontage(CharacterMontageMap.FindChecked(AnimMontageTag));
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

ALshPF_BattleGameMode* ALshPF_BattleCharacter_Base::GetBattleGameMode()
{
	if (!CachedBattleGameMode)
	{
		CachedBattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	}
	return CachedBattleGameMode;
}

bool ALshPF_BattleCharacter_Base::IsCharacterReady()
{
	//Montage 로드 및 저장 완료 && 캐릭터의 BeginPlay 호출 이후 체크
	return IsMontageReady && IsBeginPlay;
}
