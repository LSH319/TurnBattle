// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/MyLshPF_FocusableButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Controllers/LshPF_PlayerControllerBase.h"


void UMyLshPF_FocusableButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonWidget)
	{
		ButtonWidget->OnClicked.AddDynamic(this, &ThisClass::UMyLshPF_FocusableButton::OnButtonClicked);
	}
}

void UMyLshPF_FocusableButton::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	
	ALshPF_PlayerControllerBase* LshPF_PlayerController = Cast<ALshPF_PlayerControllerBase>(ButtonText->GetOwningPlayer());
	LshPF_PlayerController->SetFocusedButton(ButtonWidget);
}

void UMyLshPF_FocusableButton::SetButtonText(FText& Text)
{
	ButtonText->SetText(Text);
}

void UMyLshPF_FocusableButton::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Button Clicked"), *ButtonText->GetText().ToString());
}
