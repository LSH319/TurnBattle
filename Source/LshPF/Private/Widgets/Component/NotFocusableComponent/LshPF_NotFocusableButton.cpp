// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableButton.h"

#include "Components/TextBlock.h"
#include "Widgets/Component/LshPF_Button.h"

UButton* ULshPF_NotFocusableButton::GetButton()
{
	return ButtonWidget;
}

void ULshPF_NotFocusableButton::SetBindKeys(TArray<FKey> InBindKeys)
{
	BindKeys = InBindKeys;
}

void ULshPF_NotFocusableButton::SetButtonText(FText Text)
{
	ButtonText->SetText(Text);
}

void ULshPF_NotFocusableButton::SetButtonType(EButtonType InButtonType)
{
	ButtonType = InButtonType;
}

EButtonType ULshPF_NotFocusableButton::GetButtonType()
{
	return ButtonType;
}
