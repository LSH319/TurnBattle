// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableWidget_Status.h"

#include "Component/LshPF_BattleComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void ULshPF_NotFocusableWidget_Status::SetBattleComponent(ULshPF_BattleComponent* BattleComponent)
{
	CachedBattleComponent = BattleComponent;

	//Attribute 변경에 대한 Delegate 등록
	BattleComponent->AttributeChangedDelegate.AddUObject(this, &ThisClass::AttributeChangedCallback);
	NameText->SetText(CachedBattleComponent->GetCharacterName());
	HealthBar->SetPercent(CachedBattleComponent->GetAttribute(EAttributeType::CurrentHealth)/CachedBattleComponent->GetAttribute(EAttributeType::CurrentMaxHealth));
	ManaBar->SetPercent(CachedBattleComponent->GetAttribute(EAttributeType::CurrentMana)/CachedBattleComponent->GetAttribute(EAttributeType::CurrentMaxMana));
}

void ULshPF_NotFocusableWidget_Status::AttributeChangedCallback(EAttributeType AttributeType, float NewAttribute)
{
	switch (AttributeType)
	{
	case EAttributeType::BaseHealth:
		break;
	case EAttributeType::CurrentHealth:
		HealthBar->SetPercent(CachedBattleComponent->GetAttribute(EAttributeType::CurrentHealth)/CachedBattleComponent->GetAttribute(EAttributeType::CurrentMaxHealth));
		break;
	case EAttributeType::BaseMaxHealth:
		break;
	case EAttributeType::CurrentMaxHealth:
		break;
	case EAttributeType::BaseMana:
		break;
	case EAttributeType::CurrentMana:
		ManaBar->SetPercent(CachedBattleComponent->GetAttribute(EAttributeType::CurrentMana)/CachedBattleComponent->GetAttribute(EAttributeType::CurrentMaxMana));
		break;
	case EAttributeType::BaseMaxMana:
		break;
	case EAttributeType::CurrentMaxMana:
		break;
	case EAttributeType::BaseSpeed:
		break;
	case EAttributeType::CurrentSpeed:
		break;
	case EAttributeType::BaseAttack:
		break;
	case EAttributeType::CurrentAttack:
		break;
	case EAttributeType::BaseDefence:
		break;
	case EAttributeType::CurrentDefence:
		break;
	case EAttributeType::BaseAbilityAttack:
		break;
	case EAttributeType::CurrentAbilityAttack:
		break;
	case EAttributeType::BaseAbilityDefence:
		break;
	case EAttributeType::CurrentAbilityDefence:
		break;
	case EAttributeType::Unknown:
		break;
	}
}
