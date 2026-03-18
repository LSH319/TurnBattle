// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_Rotator_Int.h"

#include "Components/TextBlock.h"
#include "Widgets/Component/LshPF_Button.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableButton.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

void ULshPF_Rotator_Int::WidgetConfirmAction()
{
	ULshPF_FocusableWidgetBase* ParentWidget = GetTypedOuter<ULshPF_FocusableWidgetBase>();
	if (ParentWidget)
	{
		ParentWidget->WidgetConfirmAction();
	}
}

void ULshPF_Rotator_Int::WidgetBackAction()
{
	ULshPF_FocusableWidgetBase* ParentWidget = GetTypedOuter<ULshPF_FocusableWidgetBase>();
	if (ParentWidget)
	{
		ParentWidget->RemoveFromParentStack();
	}
}

void ULshPF_Rotator_Int::SetRotatorTitle(FText NewText)
{
	RotatorTitle->SetText(NewText);
}

void ULshPF_Rotator_Int::SetRotatorValue(int32 NewValue)
{
	CurrentValue = NewValue;
	RotatorValue->SetText(FText::FromString(FString::FromInt(CurrentValue)));
	OnValueChangeEvent.Broadcast(CurrentValue, RotatorKey);
}

void ULshPF_Rotator_Int::SetRotatorKey(FName NewKey)
{
	RotatorKey = NewKey;
}

void ULshPF_Rotator_Int::NativePreConstruct()
{
	Super::NativePreConstruct();

	RotatorValue->SetText(FText::FromString(FString::FromInt(CurrentValue)));
	RotatorTitle->SetColorAndOpacity(DefaultTextColor);

	PreviousButton->SetButtonText(FText::FromString(""));
	NextButton->SetButtonText(FText::FromString(""));
}

void ULshPF_Rotator_Int::NativeConstruct()
{
	Super::NativeConstruct();
	
	PreviousButton->GetButton()->OnClicked.Clear();
	PreviousButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::OnValueSubEvent);
	
	NextButton->GetButton()->OnClicked.Clear();
	NextButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::OnValueAddEvent);
}

void ULshPF_Rotator_Int::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);

	RotatorTitle->SetColorAndOpacity(FocusTextColor);
}

void ULshPF_Rotator_Int::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);

	RotatorTitle->SetColorAndOpacity(DefaultTextColor);
}

FReply ULshPF_Rotator_Int::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey InKey = InKeyEvent.GetKey();
	
	for (FKey Key : PreviousKey)
	{
		if (InKey == Key)
		{
			OnValueSubEvent();
			return FReply::Handled();
		}
	}

	for (FKey Key : NextKey)
	{
		if (InKey == Key)
		{
			OnValueAddEvent();
			return FReply::Handled();
		}
	}
	
	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void ULshPF_Rotator_Int::OnValueAddEvent()
{
	if (CurrentValue < MaxValue)
	{
		CurrentValue++;
		RotatorValue->SetText(FText::FromString(FString::FromInt(CurrentValue)));
	}
	
	OnValueChangeEvent.Broadcast(CurrentValue, RotatorKey);
}

void ULshPF_Rotator_Int::OnValueSubEvent()
{
	if (MinValue < CurrentValue)
	{
		CurrentValue--;
		RotatorValue->SetText(FText::FromString(FString::FromInt(CurrentValue)));
	}
	
	OnValueChangeEvent.Broadcast(CurrentValue, RotatorKey);
}
