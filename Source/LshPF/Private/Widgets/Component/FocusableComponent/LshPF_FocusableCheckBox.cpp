// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_FocusableCheckBox.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/LshPF_AbilityInfoTableRow.h"
#include "Widgets/Component/LshPF_Button.h"

void ULshPF_FocusableCheckBox::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void ULshPF_FocusableCheckBox::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

void ULshPF_FocusableCheckBox::WidgetConfirmAction()
{
	Super::WidgetConfirmAction();
}

void ULshPF_FocusableCheckBox::WidgetBackAction()
{
	ULshPF_FocusableWidgetBase* ParentWidget = GetTypedOuter<ULshPF_FocusableWidgetBase>();
	if (ParentWidget)
	{//부모로 포커스 변경 및 처리
		ParentWidget->SetFocus();
		ParentWidget->SetDesiredFocusTargetSelf();
	}
}

void ULshPF_FocusableCheckBox::InitCheckBox(FLshPF_AbilityInfoTableRow* TargetRow)
{
	ButtonText->SetText(TargetRow->AbilityName);
}

void ULshPF_FocusableCheckBox::SetCheckBoxKey(FName NewCheckBoxKey)
{
	CheckBoxKey = NewCheckBoxKey;
}

void ULshPF_FocusableCheckBox::SetIsCheck(bool InIsCheck)
{
	IsCheck = InIsCheck;

	CheckImage->SetColorAndOpacity(IsCheck ? CheckLinearColor : UnCheckLinearColor);
	ChangedDelegate.ExecuteIfBound(IsCheck);
}

bool ULshPF_FocusableCheckBox::IsChecked() const
{
	return IsCheck;
}

FName ULshPF_FocusableCheckBox::GetCheckBoxKey() const
{
	return CheckBoxKey;
}

void ULshPF_FocusableCheckBox::NativeConstruct()
{
	Super::NativeConstruct();

	CheckImage->SetColorAndOpacity(UnCheckLinearColor);

	ButtonWidget->OnClicked.Clear();
	ButtonWidget->OnClicked.AddDynamic(this, &ThisClass::OnClickEvent);
}

void ULshPF_FocusableCheckBox::OnClickEvent()
{
	IsCheck = !IsCheck;

	CheckImage->SetColorAndOpacity(IsCheck ? CheckLinearColor : UnCheckLinearColor);
	ChangedDelegate.ExecuteIfBound(IsCheck);
}
