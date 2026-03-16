// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LshPF_BattleComponent.h"

#include "LshPF_GameplayTags.h"
#include "Ability/LshPF_Ability.h"
#include "Interface/LshPF_BattleInterface.h"

FBattleAttributeModifier ULshPF_BattleComponent::CreateBattleAttributeModifier(
	EAttributeType TargetAttributeType, EAttributeType BaseAttributeType, EModifierType ModifierType, float DamageRatio)
{
	float ApplyModifyValue;
	if (BaseAttributeType == EAttributeType::FixedValue)
	{
		ApplyModifyValue = DamageRatio;
	}
	else
	{
		ApplyModifyValue = GetAttribute(BaseAttributeType) * DamageRatio;
	}
	
	return FBattleAttributeModifier(ApplyModifyValue, TargetAttributeType, ModifierType);
}

FBattleAttributeModifier ULshPF_BattleComponent::GetDefaultAttackAttributeModifier()
{
	return CreateBattleAttributeModifier(
			EAttributeType::CurrentHealth,
			EAttributeType::CurrentAttack,
			EModifierType::Damage_Default,
			1.f);
}

float ULshPF_BattleComponent::ApplyModifierToTarget(ULshPF_BattleComponent* ModifierActorBattleComponent,
                                                    ULshPF_BattleComponent* CauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier)
{
	switch (BattleAttributeModifier.ModifierType)
	{
	case EModifierType::Damage_Default:
	case EModifierType::Damage_Ability:
		return ApplyDamageToTarget(ModifierActorBattleComponent, CauserBattleComponent, BattleAttributeModifier);
	case EModifierType::Cure:
		return ApplyCureToTarget(ModifierActorBattleComponent, CauserBattleComponent, BattleAttributeModifier);
	case EModifierType::Unknown:
		break;
	}
	return -1.f;
}

float ULshPF_BattleComponent::ApplyDamageToTarget(ULshPF_BattleComponent* DamagedActorBattleComponent, ULshPF_BattleComponent* DamageCauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier)
{
	if (DamagedActorBattleComponent)
	{
		return DamagedActorBattleComponent->TakeDamageFromCursor(DamageCauserBattleComponent, BattleAttributeModifier);
	}

	return -1;
}

float ULshPF_BattleComponent::ApplyCureToTarget(ULshPF_BattleComponent* CuredActorBattleComponent,
	ULshPF_BattleComponent* HealCauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier)
{
	if (CuredActorBattleComponent)
	{
		return CuredActorBattleComponent->TakeCureFromCursor(HealCauserBattleComponent, BattleAttributeModifier);
	}

	return -1;
}

float ULshPF_BattleComponent::TakeDamageFromCursor(ULshPF_BattleComponent* DamageCauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier)
{
	OnTakeDamageDelegate.Broadcast();
	float ApplyDamage = BattleAttributeModifier.ModifyValue;
	
	if (IsGuard)
	{//가드 중인경우 대미지 감소 30%
		ApplyDamage = ApplyDamage * 0.7;
	}

	float DamageReduce = 0;
	switch (BattleAttributeModifier.ModifierType)
	{//공격 타입에 따른 방어력 적용
	case EModifierType::Damage_Default:
		DamageReduce = (100 - GetAttribute(EAttributeType::CurrentDefence)) / 100;
		break;
	case EModifierType::Damage_Ability:
		DamageReduce = (100 - GetAttribute(EAttributeType::CurrentAbilityDefence)) / 100;
		break;
	default:
		break;
	}
	DamageReduce = FMath::Clamp(DamageReduce, 0, 100);
	ApplyDamage = ApplyDamage * DamageReduce;
	
	SetAttribute(BattleAttributeModifier.TargetAttribute, GetAttribute(BattleAttributeModifier.TargetAttribute) - ApplyDamage);

	switch (BattleAttributeModifier.TargetAttribute)
	{
		case EAttributeType::CurrentHealth:
			if (IsDead())
			{
				OwnerDeadEvent();
				GetOwnerBattleInterface()->PlayAnimMontageByTag(LshPF_GameplayTags::LshPF_AnimMontage_Death);
			}
			else
			{
				GetOwnerBattleInterface()->PlayAnimMontageByTag(LshPF_GameplayTags::LshPF_AnimMontage_HitReact);
			}
			break;
		default:
			break;
	}
	GetOwnerBattleInterface()->ShowApplyValue(FMath::RoundToInt(ApplyDamage), true);
	
	return ApplyDamage;
}

float ULshPF_BattleComponent::TakeCureFromCursor(ULshPF_BattleComponent* CureCauserBattleComponent,
	FBattleAttributeModifier BattleAttributeModifier)
{
	OnTakeHealDelegate.Broadcast();
	float ApplyCure = BattleAttributeModifier.ModifyValue;
	SetAttribute(BattleAttributeModifier.TargetAttribute, GetAttribute(BattleAttributeModifier.TargetAttribute) + ApplyCure);
	GetOwnerBattleInterface()->PlayAnimMontageByTag(LshPF_GameplayTags::LshPF_AnimMontage_Cure);
	GetOwnerBattleInterface()->ShowApplyValue(FMath::RoundToInt(ApplyCure), false);
	return ApplyCure;
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

void ULshPF_BattleComponent::SetIsGuard(bool NewIsGuard)
{
	IsGuard = NewIsGuard;
}

FText ULshPF_BattleComponent::GetCharacterName()
{
	return CharacterName;
}

void ULshPF_BattleComponent::SetCharacterName(const FText& NewCharacterName)
{
	CharacterName = NewCharacterName;
}

bool ULshPF_BattleComponent::IsDead()
{
	return GetAttribute(EAttributeType::CurrentHealth) <= 0;
}

bool ULshPF_BattleComponent::GrantAbility(FName AbilityKey)
{
	//Ability 를 이미 보유한 경우 즉시 return
	if (AbilityMap.Contains(AbilityKey)) return false;
	
	ULshPF_Ability* NewAbility = NewObject<ULshPF_Ability>(this);
	NewAbility->SetOwnerBattleComponent(this);
	NewAbility->InitAbilityData(AbilityKey);
	AbilityMap.Add(AbilityKey, NewAbility);
	return true;
}

TArray<ULshPF_Ability*> ULshPF_BattleComponent::GetAbilityList()
{
	TArray<ULshPF_Ability*> AbilityList;

	for (auto Ability : AbilityMap)
	{
		AbilityList.Add(Ability.Value);
	}
	
	return AbilityList;
}

ILshPF_BattleInterface* ULshPF_BattleComponent::GetOwnerBattleInterface()
{
	if (!CachedOwnerBattleInterface)
	{
		if (ILshPF_BattleInterface* OwnerBattleInterface = Cast<ILshPF_BattleInterface>(GetOwner()))
		{
			CachedOwnerBattleInterface = OwnerBattleInterface;
		}
	}
	return CachedOwnerBattleInterface;
}

void ULshPF_BattleComponent::OwnerDeadEvent()
{
	GetOwnerBattleInterface()->CharacterDeath();
}
