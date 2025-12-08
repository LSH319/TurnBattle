// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

#include "Components/PanelWidget.h"
#include "Subsystems/LshPF_UISubsystem.h"


UWidget* ULshPF_FocusableWidgetBase::GetFocusWidget()
{
	return NativeGetDesiredFocusWidget();
}

bool ULshPF_FocusableWidgetBase::RemoveFromParentStack()
{
	BeforeDestroyedEvent();
	
	return GetParent()->RemoveChild(this);
}

UWidget* ULshPF_FocusableWidgetBase::NativeGetDesiredFocusWidget()
{
	UWidget* FocusWidget = BP_GetDesiredFocusWidget();

	//BP_GetDesiredFocusWidget 우선적용
	if (!FocusWidget)
	{
		return GetDesiredFocusWidget();
	}

	return FocusWidget;
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

void ULshPF_FocusableWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
}