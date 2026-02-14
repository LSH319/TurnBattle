// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BattleCharacter/LshPF_EnemyBattleCharacter.h"

#include "LshPF_GameplayTags.h"
#include "Component/LshPF_BattleComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "GameModes/LshPF_BattleGameMode.h"
#include "Subsystems/LshPF_UISubsystem.h"

void ALshPF_EnemyBattleCharacter::PostInitializeComponents()
{
	if(GetBattleGameMode())
	{
		if (const FEnemyAttribute* EnemyAttribute = GetBattleGameMode()->GetEnemyAttributeByKeyName(CharacterKeyName))
        	{
        		LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxHealth, EnemyAttribute->BaseMaxHealth);
                LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxMana, EnemyAttribute->BaseMaxMana);
                LshPF_BattleComponent->SetAttribute(EAttributeType::BaseSpeed, EnemyAttribute->BaseSpeed);
                LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAttack, EnemyAttribute->BaseAttack);
                LshPF_BattleComponent->SetAttribute(EAttributeType::BaseDefence, EnemyAttribute->BaseDefence);
                LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityAttack, EnemyAttribute->BaseAbilityAttack);
                LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityDefence, EnemyAttribute->BaseAbilityDefence);
        	}
	}
	
	Super::PostInitializeComponents();
}

void ALshPF_EnemyBattleCharacter::TurnStart()
{
	Super::TurnStart();

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->SetWidgetSwitcherVisibilityWithTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, ESlateVisibility::Hidden);
	}
}
