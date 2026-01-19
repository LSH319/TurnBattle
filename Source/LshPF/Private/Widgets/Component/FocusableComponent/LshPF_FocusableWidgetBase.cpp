// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

#include "Components/PanelWidget.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputSettings.h"
#include "Subsystems/LshPF_UISubsystem.h"


UWidget* ULshPF_FocusableWidgetBase::GetDesiredFocusTarget()
{
	return NativeGetDesiredFocusTarget();
}

bool ULshPF_FocusableWidgetBase::RemoveFromParentStack()
{
	BeforeDestroyedEvent();
	
	return GetParent()->RemoveChild(this);
}

void ULshPF_FocusableWidgetBase::WidgetConfirmAction()
{

}

void ULshPF_FocusableWidgetBase::WidgetBackAction()
{

}

UWidget* ULshPF_FocusableWidgetBase::NativeGetDesiredFocusTarget()
{
	UWidget* FocusWidget = BP_GetDesiredFocusTarget();

	//BP_GetDesiredFocusWidget 우선적용
	if (!FocusWidget)
	{
		if (DesiredFocusTarget)
		{
			return DesiredFocusTarget;
		}
		return GetDesiredFocusWidget();
	}

	return FocusWidget;
}

void ULshPF_FocusableWidgetBase::BP_BindChildWidgetGetFocus(ULshPF_FocusableWidgetBase* InFocusTargetWidget)
{
	InFocusTargetWidget->OnFocusWidgetChanged.AddUObject(this, &ThisClass::SetDesiredFocusTarget);

	if (!DesiredFocusTarget && InFocusTargetWidget)
	{
		DesiredFocusTarget = InFocusTargetWidget;
	}
}

void ULshPF_FocusableWidgetBase::BeforeDestroyedEvent()
{
	int32 Index = GetParent()->GetChildIndex(this);
	
	if (OnWidgetDestroyed.IsBound())
	{
		OnWidgetDestroyed.Execute(Index);
	}

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		if (HasFocusedDescendants() && UISubsystem->FindNewFocusWidget.IsBound())
		{
			UISubsystem->FindNewFocusWidget.Execute();
		}
	}
}

void ULshPF_FocusableWidgetBase::UpdateInputDevice()
{
	FHardwareDeviceIdentifier HardwareDeviceIdentifier = UInputDeviceSubsystem::Get()->GetMostRecentlyUsedHardwareDevice(GetOwningPlayer()->GetPlatformUserId());

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->SetRecentlyInputDeviceType(HardwareDeviceIdentifier.PrimaryDeviceType);
	}
}

void ULshPF_FocusableWidgetBase::SetDesiredFocusTarget(ULshPF_FocusableWidgetBase* InFocusTargetWidget)
{
	if (InFocusTargetWidget)
	{
		DesiredFocusTarget = InFocusTargetWidget;
	}
}

void ULshPF_FocusableWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
}

FReply ULshPF_FocusableWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey Key = InKeyEvent.GetKey();
	if (Key == EKeys::Gamepad_DPad_Up||
		Key == EKeys::Gamepad_DPad_Down ||
		Key == EKeys::Gamepad_DPad_Right ||
		Key == EKeys::Gamepad_DPad_Left)
	{
		UpdateInputDevice();
	}
	
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply ULshPF_FocusableWidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	UpdateInputDevice();
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
