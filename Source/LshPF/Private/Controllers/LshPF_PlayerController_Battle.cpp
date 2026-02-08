// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerController_Battle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ALshPF_PlayerController_Battle::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (BattleCommandMappingContext)
			{
				InputSystem->AddMappingContext(BattleCommandMappingContext, 6);
			}
		}
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	/*EnhancedInputComponent->BindAction(BattleConfirmAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	EnhancedInputComponent->BindAction(BattleBackAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	EnhancedInputComponent->BindAction(BattleGuardAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	EnhancedInputComponent->BindAction(BattleSkillAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	EnhancedInputComponent->BindAction(BattleItemAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);*/
	
}
