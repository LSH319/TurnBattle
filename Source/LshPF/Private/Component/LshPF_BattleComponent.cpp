// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LshPF_BattleComponent.h"

#include "Interface/LshPF_BattleInterface.h"

FDamageInfo ULshPF_BattleComponent::CreateDamageInfo(float InDamage, bool InIsCritical)
{
	return FDamageInfo(InDamage, InIsCritical);
}

float ULshPF_BattleComponent::ApplyDamageToTarget(ULshPF_BattleComponent* DamagedActorBattleComponent, ULshPF_BattleComponent* DamageCauserBattleComponent, FDamageInfo DamageInfo)
{
	if (DamagedActorBattleComponent)
	{
		return DamagedActorBattleComponent->TakeDamageFromCursor(DamageCauserBattleComponent, DamageInfo);
	}

	return -1;
}

float ULshPF_BattleComponent::TakeDamageFromCursor(ULshPF_BattleComponent* DamageCauserBattleComponent, FDamageInfo DamageInfo)
{
	OnTakeDamageDelegate.Broadcast();
	float ApplyDamage = DamageInfo.Damage;
	SetAttribute(EAttributeType::CurrentHealth, GetAttribute(EAttributeType::CurrentHealth) - ApplyDamage);

	if (GetAttribute(EAttributeType::CurrentHealth) <= 0)
	{
		//todo : 사망처리
		
		/*
		if (ILshPF_BattleInterface* OwnerBattleInterface = Cast<ILshPF_BattleInterface>(GetOwner()))
		{
		ILshPF_BattleInterface 에 Die 로직 추가 후 호출예정
			OwnerBattleInterface->Die();
		}
		*/
	}
	
	return ApplyDamage;
}

float ULshPF_BattleComponent::GetAttribute(EAttributeType AttributeType)
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

void ULshPF_BattleComponent::SetAttribute(EAttributeType AttributeType, float NewAttribute)
{
	switch (AttributeType)
	{
	case EAttributeType::BaseHealth:
		BaseHealth = FMath::Clamp(NewAttribute, 0, GetAttribute(EAttributeType::BaseMaxHealth));
		break;
	case EAttributeType::CurrentHealth:
		CurrentHealth = FMath::Clamp(NewAttribute, 0, GetAttribute(EAttributeType::CurrentMaxHealth));
		break;
	case EAttributeType::BaseMaxHealth:
		BaseMaxHealth = NewAttribute;
		break;
	case EAttributeType::CurrentMaxHealth:
		CurrentMaxHealth = NewAttribute;
		break;
	case EAttributeType::BaseMana:
		BaseMana = FMath::Clamp(NewAttribute, 0, GetAttribute(EAttributeType::BaseMaxMana));
		break;
	case EAttributeType::CurrentMana:
		CurrentMana = FMath::Clamp(NewAttribute, 0, GetAttribute(EAttributeType::CurrentMaxMana));
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

	AttributeChangedDelegate.Broadcast(AttributeType, NewAttribute);
}

void ULshPF_BattleComponent::SetAllCurrentAttributeToBaseAttribute()
{
	SetAttribute(EAttributeType::CurrentMaxHealth, GetAttribute(EAttributeType::BaseMaxHealth));
	SetAttribute(EAttributeType::CurrentMaxMana, GetAttribute(EAttributeType::BaseMaxMana));

	SetAttribute(EAttributeType::CurrentHealth, GetAttribute(EAttributeType::BaseHealth));
	SetAttribute(EAttributeType::CurrentMana, GetAttribute(EAttributeType::BaseMana));
	SetAttribute(EAttributeType::CurrentSpeed, GetAttribute(EAttributeType::BaseSpeed));
	SetAttribute(EAttributeType::CurrentAttack, GetAttribute(EAttributeType::BaseAttack));
	SetAttribute(EAttributeType::CurrentDefence, GetAttribute(EAttributeType::BaseDefence));
	SetAttribute(EAttributeType::CurrentAbilityAttack, GetAttribute(EAttributeType::BaseAbilityAttack));
	SetAttribute(EAttributeType::CurrentAbilityDefence, GetAttribute(EAttributeType::BaseAbilityDefence));
}

FText ULshPF_BattleComponent::GetCharacterName()
{
	return CharacterName;
}
