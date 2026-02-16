// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BattleCharacter/LshPF_PlayerBattleCharacter.h"

#include "LshPF_GameplayTags.h"
#include "Component/LshPF_BattleComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "Controllers/LshPF_PlayerController_Battle.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LshPF_UISubsystem.h"

void ALshPF_PlayerBattleCharacter::PostInitializeComponents()
{
	//PlayerCharacter 는 Montage 를 미리 설정해두기 때문에 true
	IsMontageReady = true;
	
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxHealth, GetBaseAttributeFromCurveTable(EAttributeType::BaseMaxHealth, CharacterLevel));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxMana, GetBaseAttributeFromCurveTable(EAttributeType::BaseMaxMana, CharacterLevel));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseSpeed, GetBaseAttributeFromCurveTable(EAttributeType::BaseSpeed, CharacterLevel));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAttack, GetBaseAttributeFromCurveTable(EAttributeType::BaseAttack, CharacterLevel));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseDefence, GetBaseAttributeFromCurveTable(EAttributeType::BaseDefence, CharacterLevel));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityAttack, GetBaseAttributeFromCurveTable(EAttributeType::BaseAbilityAttack, CharacterLevel));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityDefence, GetBaseAttributeFromCurveTable(EAttributeType::BaseAbilityDefence, CharacterLevel)); 

	Super::PostInitializeComponents();
}

void ALshPF_PlayerBattleCharacter::TurnStart()
{
	Super::TurnStart();
	
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->SetWidgetSwitcherVisibilityWithTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, ESlateVisibility::SelfHitTestInvisible);
	}
	GetBattlePlayerController()->SetIsEnableInput(true);
}

void ALshPF_PlayerBattleCharacter::TurnEnd()
{
	GetBattlePlayerController()->SetIsEnableInput(false);
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->SetWidgetSwitcherVisibilityWithTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, ESlateVisibility::Hidden);
	}
	Super::TurnEnd();
}

bool ALshPF_PlayerBattleCharacter::IsPlayerCharacter()
{
	return true;
}

ALshPF_PlayerController_Battle* ALshPF_PlayerBattleCharacter::GetBattlePlayerController()
{
	if (!CachedPlayerController)
	{
		CachedPlayerController = Cast<ALshPF_PlayerController_Battle>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
	return CachedPlayerController;;
}

float ALshPF_PlayerBattleCharacter::GetBaseAttributeFromCurveTable(EAttributeType AttributeType, int32 Level)
{
	FRealCurve* Curve = nullptr;

	if (CharacterAttributeData)
	{
		switch (AttributeType)
        {
        	case EAttributeType::BaseMaxHealth:
        		Curve = CharacterAttributeData->FindCurve(FName("Attribute.MaxHealth"), FString("Attribute Name Error"));
        		break;
        	case EAttributeType::BaseMaxMana:
        		Curve = CharacterAttributeData->FindCurve(FName("Attribute.MaxMana"), FString("Attribute Name Error"));
        		break;
        	case EAttributeType::BaseSpeed:
        		Curve = CharacterAttributeData->FindCurve(FName("Attribute.Speed"), FString("Attribute Name Error"));
        		break;
        	case EAttributeType::BaseAttack:
        		Curve = CharacterAttributeData->FindCurve(FName("Attribute.Attack"), FString("Attribute Name Error"));
        		break;
        	case EAttributeType::BaseDefence:
        		Curve = CharacterAttributeData->FindCurve(FName("Attribute.Defence"), FString("Attribute Name Error"));
        		break;
        	case EAttributeType::BaseAbilityAttack:
        		Curve = CharacterAttributeData->FindCurve(FName("Attribute.AbilityAttack"), FString("Attribute Name Error"));
        		break;
        	case EAttributeType::BaseAbilityDefence:
        		Curve = CharacterAttributeData->FindCurve(FName("Attribute.AbilityDefence"), FString("Attribute Name Error"));
        		break;
        	default:
        		return -1.f;
        }
	}
	

	if (Curve)
	{
		return Curve->Eval(Level);
	}
	return -1.f;
}
