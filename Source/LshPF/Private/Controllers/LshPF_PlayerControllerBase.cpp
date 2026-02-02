// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

UInputAction* ALshPF_PlayerControllerBase::GetDefaultConfirmAction()
{
	return DefaultConfirmAction;
}

UInputAction* ALshPF_PlayerControllerBase::GetDefaultBackAction()
{
	return DefaultBackAction;
}

TArray<FKey> ALshPF_PlayerControllerBase::GetKeysByInputAction(const UInputAction* InAction)
{
	TArray<FKey> ReturnKeys;
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			ReturnKeys = InputSystem->QueryKeysMappedToAction(InAction);
		}
	}
	return ReturnKeys;
}

void ALshPF_PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputDeviceCheckMappingContext)
			{
				InputSystem->AddMappingContext(InputDeviceCheckMappingContext, 99);
			}
			if (DefaultMappingContext)
			{
				InputSystem->AddMappingContext(DefaultMappingContext, 5);
			}
		}
	}
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(InputDeviceCheckAction, ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	
	EnhancedInputComponent->BindAction(DefaultConfirmAction, ETriggerEvent::Started, this, &ThisClass::DefaultConfirmAction_Callback);
	EnhancedInputComponent->BindAction(DefaultBackAction, ETriggerEvent::Started, this, &ThisClass::DefaultBackAction_Callback);
}

void ALshPF_PlayerControllerBase::DefaultConfirmAction_Callback(const FInputActionValue& Value)
{
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		if (ULshPF_FocusableWidgetBase* FocusTarget = Cast<ULshPF_FocusableWidgetBase>(UISubsystem->GetFocusTargetWidget()))
		{
			FocusTarget->WidgetConfirmAction();
		}
	}
}

void ALshPF_PlayerControllerBase::DefaultBackAction_Callback(const FInputActionValue& Value)
{
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		if (ULshPF_FocusableWidgetBase* FocusTarget = Cast<ULshPF_FocusableWidgetBase>(UISubsystem->GetFocusTargetWidget()))
		{
			FocusTarget->WidgetBackAction();
		}
	}
}

void ALshPF_PlayerControllerBase::InputDeviceCheckAction_Callback(const FInputActionValue& Value)
{
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->SetRecentlyInputDeviceType();
		if (ULshPF_FocusableWidgetBase* FocusTarget = Cast<ULshPF_FocusableWidgetBase>(UISubsystem->GetFocusTargetWidget()))
		{
			FocusTarget->SetFocus();
		}
	}
}