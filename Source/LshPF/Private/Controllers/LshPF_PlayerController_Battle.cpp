// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerController_Battle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ALshPF_PlayerController_Battle::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	/*
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(BattleOpenSkillListAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	*/
}
