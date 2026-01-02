// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/Button.h"
#include "InputMappingContext.h"

void ALshPF_PlayerControllerBase::SetFocusedButton(UButton* FocusedButton)
{
	FocusedButtonWidget.Reset();
	FocusedButtonWidget = FocusedButton;
}

void ALshPF_PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!DefaultMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(DefaultMappingContext.LoadSynchronous(), 0);
			}
		}
	}
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(DefaultConfirmAction.LoadSynchronous(), ETriggerEvent::Started, this, &ThisClass::DefaultConfirmAction_Callback);
}

void ALshPF_PlayerControllerBase::DefaultConfirmAction_Callback()
{
	if (FocusedButtonWidget.IsValid())
	{
		FocusedButtonWidget.Get()->SetFocus();
		FocusedButtonWidget.Get()->OnClicked.Broadcast();
	}
}
