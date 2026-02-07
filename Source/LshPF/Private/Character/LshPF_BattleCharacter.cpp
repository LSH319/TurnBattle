// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LshPF_BattleCharacter.h"

#include "Component/LshPF_BattleComponent.h"
#include "GameModes/LshPF_BattleGameMode.h"

ALshPF_BattleCharacter::ALshPF_BattleCharacter()
{
	LshPF_BattleComponent = CreateDefaultSubobject<ULshPF_BattleComponent>("BattleComponent");
}

ULshPF_BattleComponent* ALshPF_BattleCharacter::GetBattleComponent() const
{
	return LshPF_BattleComponent;
}

void ALshPF_BattleCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//todo : LshPF_BattleComponent 값 초기화

	LshPF_BattleComponent->SetAllCurrentAttributeToBaseAttribute();
}

void ALshPF_BattleCharacter::BeginPlay()
{
	Super::BeginPlay();

	ALshPF_BattleGameMode* BattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	BattleGameMode->RequestAddTurnTable(this);
}

int32 ALshPF_BattleCharacter::GetAttribute(EAttributeType AttributeType)
{
	return LshPF_BattleComponent->GetAttribute(AttributeType);
}

void ALshPF_BattleCharacter::SetAttribute(EAttributeType AttributeType, int32 NewAttribute)
{
	LshPF_BattleComponent->SetAttribute(AttributeType, NewAttribute);
}

void ALshPF_BattleCharacter::TurnStart()
{
	
}

void ALshPF_BattleCharacter::TurnEnd()
{
	ALshPF_BattleGameMode* BattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	BattleGameMode->TargetTurnEnd(this);
}
