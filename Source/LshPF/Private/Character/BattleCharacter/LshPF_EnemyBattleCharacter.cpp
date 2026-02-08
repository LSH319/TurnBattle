// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BattleCharacter/LshPF_EnemyBattleCharacter.h"

#include "Component/LshPF_BattleComponent.h"
#include "GameModes/LshPF_BattleGameMode.h"

void ALshPF_EnemyBattleCharacter::PostInitializeComponents()
{
	FEnemyAttribute* EnemyAttribute = GetBattleGameMode()->GetEnemyAttributeByKeyName(EnemyKeyName);
	
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxHealth, EnemyAttribute->BaseMaxHealth);
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxMana, EnemyAttribute->BaseMaxMana);
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseSpeed, EnemyAttribute->BaseSpeed);
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAttack, EnemyAttribute->BaseAttack);
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseDefence, EnemyAttribute->BaseDefence);
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityAttack, EnemyAttribute->BaseAbilityAttack);
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityDefence, EnemyAttribute->BaseAbilityDefence);

	Super::PostInitializeComponents();
}
