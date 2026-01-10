// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_FocusableButton.h"

#include "Components/TextBlock.h"
#include "Widgets/Component/LshPF_Button.h"

void ULshPF_FocusableButton::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);

	OnFocusWidgetChanged.Broadcast(this);
}

void ULshPF_FocusableButton::WidgetConfirmAction()
{
	ButtonWidget->OnClicked.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("%s::WidgetConfirmAction"), *GetName());
}

void ULshPF_FocusableButton::WidgetBackAction()
{
	UE_LOG(LogTemp, Warning, TEXT("%s::WidgetBackAction"), *GetName());
}

void ULshPF_FocusableButton::SetButtonText(FText Text)
{
	ButtonText->SetText(Text);
}