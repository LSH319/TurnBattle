// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/MyLshPF_FocusableButton.h"

#include "Components/TextBlock.h"
#include "Widgets/Component/LshPF_Button.h"


void UMyLshPF_FocusableButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonWidget)
	{
		ButtonWidget->OnClicked.AddDynamic(this, &ThisClass::UMyLshPF_FocusableButton::WidgetConfirmAction);
	}
}

void UMyLshPF_FocusableButton::WidgetConfirmAction()
{
	UE_LOG(LogTemp, Warning, TEXT("%s::WidgetConfirmAction"), *GetName());
}

void UMyLshPF_FocusableButton::WidgetBackAction()
{
	UE_LOG(LogTemp, Warning, TEXT("%s::WidgetBackAction"), *GetName());
}

void UMyLshPF_FocusableButton::SetButtonText(FText& Text)
{
	ButtonText->SetText(Text);
}
