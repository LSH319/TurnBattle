// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableWidgetBase.h"

void ULshPF_NotFocusableWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(false);
}
