// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

UWidget* ULshPF_FocusableWidgetBase::GetDesiredFocusWidget()
{
	return NativeGetDesiredFocusWidget();
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

void ULshPF_FocusableWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);
}
