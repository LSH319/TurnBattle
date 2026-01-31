// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

#include "Components/PanelWidget.h"
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
		if (GetDesiredFocusWidget())
		{
			return GetDesiredFocusWidget();
		}
		else
		{
			return this;
		}
	}

	return FocusWidget;
}

void ULshPF_FocusableWidgetBase::BP_BindChildWidgetGetFocus(ULshPF_FocusableWidgetBase* InFocusTargetWidget)
{
	//자식이 Focus 를 받은 경우 호출되는 Delegate
	InFocusTargetWidget->OnFocusWidgetChanged.AddUObject(this, &ThisClass::SetDesiredFocusTarget);

	//DesiredFocusTarget 이 null 일경우 처음 호출한 Widget 을 사용
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
		//저장된 Switcher 에 Index 전달
		//Widget 전달 시 올바르지 않은 값이 전달되는 경우 발생
		OnWidgetDestroyed.Execute(Index);
	}

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		if (HasFocusedDescendants() && UISubsystem->FindNewFocusWidget.IsBound())
		{
			//삭제되는 Widget 이 Focus 를 가지고 있는 경우 새로운 Focus Target 을 찾아 설정하도록 호출
			UISubsystem->FindNewFocusWidget.Execute();
		}
	}
}

void ULshPF_FocusableWidgetBase::UpdateInputDevice()
{
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->SetRecentlyInputDeviceType();
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
		//GamePad 의 DPad 입력시 InputDevice 가 Update 되도록 추가
		//별도 처리 없이 사용할 경우 DPad 입력시 Enhanced Input 까지 전달되지 않아 추가한 코드
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
