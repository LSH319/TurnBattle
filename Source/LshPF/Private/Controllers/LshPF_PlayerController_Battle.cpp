// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerController_Battle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameModes/LshPF_BattleGameMode.h"

void ALshPF_PlayerController_Battle::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	/*
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(BattleOpenSkillListAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	*/
}

ALshPF_BattleGameMode* ALshPF_PlayerController_Battle::GetBattleGameMode()
{
	if (!CachedBattleGameMode)
	{
		CachedBattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	}
	return CachedBattleGameMode;
}
