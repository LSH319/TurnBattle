// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

void ALshPF_PlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputDeviceCheckMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(InputDeviceCheckMappingContext.LoadSynchronous(), 99);
			}
			if (!DefaultMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(DefaultMappingContext.LoadSynchronous(), 5);
			}
		}
	}
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(InputDeviceCheckAction.LoadSynchronous(), ETriggerEvent::Started, this, &ThisClass::InputDeviceCheckAction_Callback);
	
	EnhancedInputComponent->BindAction(DefaultConfirmAction.LoadSynchronous(), ETriggerEvent::Started, this, &ThisClass::DefaultConfirmAction_Callback);
	EnhancedInputComponent->BindAction(DefaultBackAction.LoadSynchronous(), ETriggerEvent::Started, this, &ThisClass::DefaultBackAction_Callback);
}

void ALshPF_PlayerControllerBase::DefaultConfirmAction_Callback()
{
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		if (ULshPF_FocusableWidgetBase* FocusTarget = Cast<ULshPF_FocusableWidgetBase>(UISubsystem->GetFocusTargetWidget()))
		{
			FocusTarget->WidgetConfirmAction();
		}
	}
}

void ALshPF_PlayerControllerBase::DefaultBackAction_Callback()
{
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		if (ULshPF_FocusableWidgetBase* FocusTarget = Cast<ULshPF_FocusableWidgetBase>(UISubsystem->GetFocusTargetWidget()))
		{
			FocusTarget->WidgetBackAction();
		}
	}
}

void ALshPF_PlayerControllerBase::InputDeviceCheckAction_Callback()
{
	FHardwareDeviceIdentifier HardwareDeviceIdentifier = UInputDeviceSubsystem::Get()->GetMostRecentlyUsedHardwareDevice(GetPlatformUserId());
	FString Device = HardwareDeviceIdentifier.PrimaryDeviceType == EHardwareDevicePrimaryType::KeyboardAndMouse ? "KeyboardAndMouse" : "Gamepad";
	UE_LOG(LogTemp, Warning, TEXT("Clicked by %s"), *Device);
	//1 -> 키보드 2-> 패드
	/*
	 * 버튼으로 입력 컨슘 > 버튼에서 직접 디바이스 전송
	 * 아닐경우 PC 에서 아무키 바인딩한 IA 를 통해 디바이스 전송
	 * SButton 쪽에서 Virtual Accept 로 키를 Handle 해버림.이 방식이 아니면  Sbutton을 커스텀해서 사용필요
	 */
}
