// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/LshPF_Ability.h"

#include "LshPF_GameplayTags.h"
#include "Component/LshPF_BattleComponent.h"
#include "Controllers/LshPF_PlayerController_Battle.h"
#include "GameModes/LshPF_BattleGameMode.h"
#include "Interface/LshPF_BattleInterface.h"
#include "Kismet/GameplayStatics.h"

void ULshPF_Ability::SetOwnerBattleComponent(ULshPF_BattleComponent* OwnerBattleComponentPointer)
{
	OwnerBattleComponent = OwnerBattleComponentPointer;
}

void ULshPF_Ability::InitAbilityData(FName AbilityKey)
{
	FLshPF_AbilityInfoTableRow* AbilityInfo = GetBattleGameMode()->GetAbilityInfoByKeyName(AbilityKey);
	AbilityName = AbilityInfo->AbilityName;
	DamageRatioAttributeType = AbilityInfo->DamageRatioAttributeType;
	DamageRatio = AbilityInfo->DamageRatio;
	TargetAttributeType = AbilityInfo->TargetAttributeType;
	CostAttributeType = AbilityInfo->CostAttributeType;
	AbilityCost = AbilityInfo->AbilityCost;
	TargetType = AbilityInfo->TargetType;
	AbilityType = AbilityInfo->AbilityType;
}

bool ULshPF_Ability::IsCanActivate()
{
	if (OwnerBattleComponent.IsValid())
	{
		if (OwnerBattleComponent->GetAttribute(CostAttributeType) >= AbilityCost)
		{
			//Attribute 가 Cost 보다 높은경우, True
			return true;
		}
	}
	
	return false;
}

void ULshPF_Ability::CommitAbility()
{
	if (IsCanActivate())
	{//IsCanActivate 에서 true 인 경우는 OwnerBattleComponent 의 Valid 체크도 통과한 경우
		//Attribute 를 Cost 만큼 감소
		OwnerBattleComponent->SetAttribute(CostAttributeType, OwnerBattleComponent->GetAttribute(CostAttributeType) - AbilityCost);
		ActivateAbility();
	}
}

void ULshPF_Ability::ActivateAbility()
{
	ILshPF_BattleInterface* TurnCharacter = GetBattleGameMode()->GetRecentOwingTurnCharacter();
	TurnCharacter->PlayAnimMontageByTag(LshPF_GameplayTags::LshPF_AnimMontage_Skill);
}

FBattleAttributeModifier ULshPF_Ability::GetAbilityModifier()
{
	ILshPF_BattleInterface* TurnCharacter = GetBattleGameMode()->GetRecentOwingTurnCharacter();
	return TurnCharacter->GetBattleComponent()->CreateBattleAttributeModifier(TargetAttributeType, DamageRatioAttributeType, AbilityType, DamageRatio);
}

FString ULshPF_Ability::GetDescription()
{
	FString Description = "";
	
	switch (AbilityType)
	{
	case EModifierType::Damage_Default:
	case EModifierType::Damage_Ability:
		Description.Append("Give damage to ");
		break;
	case EModifierType::Cure:
		Description.Append("Give cure to ");
		break;
	default:
		break;
	}
	
	switch (TargetType)
	{
	case ETargetType::EnemySingle:
		Description.Append("one enemy ");
		break;
	case ETargetType::EnemyAll:
		Description.Append("all enemies ");
		break;
	case ETargetType::PlayerSingle:
		Description.Append("one friend ");
		break;
	case ETargetType::PlayerAll:
		Description.Append("all friends ");
		break;
	default:
		break;
	}

	Description = Description + FString::Printf(TEXT("[%.0f%% of "), DamageRatio * 100);
	Description.Append(EAttributeTypeToString(DamageRatioAttributeType) + "]");
	
	return Description;
}

FText ULshPF_Ability::GetAbilityName()
{
	return AbilityName;
}

FString ULshPF_Ability::GetCostAttributeType()
{
	return EAttributeTypeToString(CostAttributeType);
}

float ULshPF_Ability::GetAbilityCost()
{
	return AbilityCost;
}

ETargetType ULshPF_Ability::GetTargetType()
{
	return TargetType;
}

TArray<ULshPF_BattleComponent*> ULshPF_Ability::GetTargetBattleComponents()
{
	TArray<ULshPF_BattleComponent*> TargetBattleComponents;
	switch (TargetType)
	{
	case ETargetType::EnemySingle:
	case ETargetType::PlayerSingle:
		TargetBattleComponents.Add(GetBattlePlayerController()->GetTargetBattleComponent());
		break;
	case ETargetType::EnemyAll:
		for (ILshPF_BattleInterface* TargetBattleInterface : GetBattleGameMode()->GetEnemyCharacters())
		{
			TargetBattleComponents.Add(TargetBattleInterface->GetBattleComponent());
		}
		break;
	case ETargetType::PlayerAll:
		for (ILshPF_BattleInterface* TargetBattleInterface : GetBattleGameMode()->GetPlayerCharacters())
		{
			TargetBattleComponents.Add(TargetBattleInterface->GetBattleComponent());
		}
		break;
	case ETargetType::Unknown:
		break;
	}
	return TargetBattleComponents;
}

ALshPF_BattleGameMode* ULshPF_Ability::GetBattleGameMode()
{
	if (!CachedBattleGameMode.IsValid())
	{
		CachedBattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	}
	return CachedBattleGameMode.Get();
}

ALshPF_PlayerController_Battle* ULshPF_Ability::GetBattlePlayerController()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<ALshPF_PlayerController_Battle>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
	return CachedPlayerController.Get();
}

FString ULshPF_Ability::EAttributeTypeToString(EAttributeType AttributeType)
{
	FString ReturnString;
	switch (AttributeType)
	{
	case EAttributeType::BaseHealth:
	case EAttributeType::CurrentHealth:
		ReturnString = "Health";
		break;
	case EAttributeType::BaseMaxHealth:
	case EAttributeType::CurrentMaxHealth:
		ReturnString = "MaxHealth";
		break;
	case EAttributeType::BaseMana:
	case EAttributeType::CurrentMana:
		ReturnString = "Mana";
		break;
	case EAttributeType::BaseMaxMana:
	case EAttributeType::CurrentMaxMana:
		ReturnString = "MaxMana";
		break;
	case EAttributeType::BaseSpeed:
	case EAttributeType::CurrentSpeed:
		ReturnString = "Speed";
		break;
	case EAttributeType::BaseAttack:
	case EAttributeType::CurrentAttack:
		ReturnString = "Attack";
		break;
	case EAttributeType::BaseDefence:
	case EAttributeType::CurrentDefence:
		ReturnString = "Defence";
		break;
	case EAttributeType::BaseAbilityAttack:
	case EAttributeType::CurrentAbilityAttack:
		ReturnString = "AbilityAttack";
		break;
	case EAttributeType::BaseAbilityDefence:
	case EAttributeType::CurrentAbilityDefence:
		ReturnString = "AbilityDefence";
		break;
	case EAttributeType::Unknown:
	default:
		break;
	}
	return ReturnString;
}
