// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_FocusableButton.h"

#include "Components/TextBlock.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/LshPF_Button.h"

void ULshPF_FocusableButton::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);

	//Focus 를 흭득한 경우 Self 를 Broadcast
	OnFocusWidgetChanged.Broadcast(this);
	//Focus 를 흭득한 경우 Text 색상 변경
	ButtonText->SetColorAndOpacity(OnFocusTextSlateColor);
	//Focus 를 흭득한 경우 Description Text 변경
	ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld());
	UISubsystem->OnButtonDescriptionTextUpdated.Broadcast(this, ButtonDescriptionText);
}

void ULshPF_FocusableButton::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	//Focus 를 흭득한 경우 Text 색상 변경
	ButtonText->SetColorAndOpacity(BaseTextSlateColor);
}

void ULshPF_FocusableButton::WidgetConfirmAction()
{
	ButtonWidget->OnClicked.Broadcast();
}

void ULshPF_FocusableButton::WidgetBackAction()
{
}

void ULshPF_FocusableButton::SetButtonText(FText Text)
{
	ButtonText->SetText(Text);
}

void ULshPF_FocusableButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
	ButtonText->SetColorAndOpacity(BaseTextSlateColor);
}
