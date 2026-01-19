// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableWidgetBase.h"

#include "Controllers/LshPF_PlayerControllerBase.h"

void ULshPF_NotFocusableWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(false);
}

ALshPF_PlayerControllerBase* ULshPF_NotFocusableWidgetBase::GetLshPF_PlayerController()
{
	return Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer());;
}
