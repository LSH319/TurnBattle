// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LshPF_BattleComponent.h"

float ULshPF_BattleComponent::ApplyDamageToTarget(AActor* DamagedActor, AActor* DamageCauser, FDamageInfo DamageInfo)
{
	if (ULshPF_BattleComponent* TargetBattleComponent = DamagedActor->FindComponentByClass<ULshPF_BattleComponent>())
	{
		return TargetBattleComponent->TakeDamageFromCursor(DamageCauser, DamageInfo);
	}

	return -1;
}

float ULshPF_BattleComponent::TakeDamageFromCursor(AActor* DamageCauser, FDamageInfo DamageInfo)
{
	OnTakeDamageDelegate.Broadcast();
	
	CurrentHealth = CurrentHealth - DamageInfo.Damage;
	if (CurrentHealth <= 0)
	{
		//todo : 사망처리
	}
	return DamageInfo.Damage;
}

int32 ULshPF_BattleComponent::GetAttribute(EAttributeType AttributeType)
{
	switch (AttributeType)
	{
		case EAttributeType::BaseHealth:
			return BaseHealth;
		case EAttributeType::CurrentHealth:
			return CurrentHealth;
		case EAttributeType::BaseMaxHealth:
			return BaseMaxHealth;
		case EAttributeType::CurrentMaxHealth:
			return CurrentMaxHealth;
		case EAttributeType::BaseMana:
			return BaseMana;
		case EAttributeType::CurrentMana:
			return CurrentMana;
		case EAttributeType::BaseMaxMana:
			return BaseMaxMana;
		case EAttributeType::CurrentMaxMana:
			return CurrentMaxMana;
		case EAttributeType::BaseSpeed:
			return BaseSpeed;
		case EAttributeType::CurrentSpeed:
			return CurrentSpeed;
		case EAttributeType::BaseAttack:
			return BaseAttack;
		case EAttributeType::CurrentAttack:
			return CurrentAttack;
		case EAttributeType::BaseDefence:
			return BaseDefence;
		case EAttributeType::CurrentDefence:
			return CurrentDefence;
		case EAttributeType::BaseAbilityAttack:
			return BaseAbilityAttack;
		case EAttributeType::CurrentAbilityAttack:
			return CurrentAbilityAttack;
		case EAttributeType::BaseAbilityDefence:
			return BaseAbilityDefence;
		case EAttributeType::CurrentAbilityDefence:
			return CurrentAbilityDefence;
		case EAttributeType::Unknown:
		default:
			return -1;
	}
}

void ULshPF_BattleComponent::SetAttribute(EAttributeType AttributeType, int32 NewAttribute)
{
	switch (AttributeType)
	{
	case EAttributeType::BaseHealth:
		BaseHealth = NewAttribute;
		break;
	case EAttributeType::CurrentHealth:
		CurrentHealth = NewAttribute;
		break;
	case EAttributeType::BaseMaxHealth:
		BaseMaxHealth = NewAttribute;
		break;
	case EAttributeType::CurrentMaxHealth:
		CurrentMaxHealth = NewAttribute;
		break;
	case EAttributeType::BaseMana:
		BaseMana = NewAttribute;
		break;
	case EAttributeType::CurrentMana:
		CurrentMana = NewAttribute;
		break;
	case EAttributeType::BaseMaxMana:
		BaseMaxMana = NewAttribute;
		break;
	case EAttributeType::CurrentMaxMana:
		CurrentMaxMana = NewAttribute;
		break;
	case EAttributeType::BaseSpeed:
		BaseSpeed = NewAttribute;
		break;
	case EAttributeType::CurrentSpeed:
		CurrentSpeed = NewAttribute;
		break;
	case EAttributeType::BaseAttack:
		BaseAttack = NewAttribute;
		break;
	case EAttributeType::CurrentAttack:
		CurrentAttack = NewAttribute;
		break;
	case EAttributeType::BaseDefence:
		BaseDefence = NewAttribute;
		break;
	case EAttributeType::CurrentDefence:
		CurrentDefence = NewAttribute;
		break;
	case EAttributeType::BaseAbilityAttack:
		BaseAbilityAttack = NewAttribute;
		break;
	case EAttributeType::CurrentAbilityAttack:
		CurrentAbilityAttack = NewAttribute;
		break;
	case EAttributeType::BaseAbilityDefence:
		BaseAbilityDefence = NewAttribute;
		break;
	case EAttributeType::CurrentAbilityDefence:
		CurrentAbilityDefence = NewAttribute;
		break;
	case EAttributeType::Unknown:
	default:
		break;
	}
}

void ULshPF_BattleComponent::SetAllCurrentAttributeToBaseAttribute()
{
	CurrentHealth = BaseHealth;
	CurrentMaxHealth = BaseMaxHealth;
	CurrentMana = BaseMana;
	CurrentMaxMana = BaseMaxMana;
	CurrentSpeed = BaseSpeed;
	CurrentAttack = BaseAttack;
	CurrentDefence = BaseDefence;
	CurrentAbilityAttack = BaseAbilityAttack;
	CurrentAbilityDefence = BaseAbilityDefence;
}
