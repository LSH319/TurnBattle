// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_CharacterCheckList.h"

#include "Components/DynamicEntryBox.h"
#include "Components/Image.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableCheckBox.h"
#include "Data/LshPF_AbilityInfoTableRow.h"
#include "Data/PlayerCharacterInfo.h"

void ULshPF_CharacterCheckList::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	BackgroundImage->SetColorAndOpacity(OnFocusBackgroundColor);
	OnFocusWidgetChanged.Broadcast(this);
}

void ULshPF_CharacterCheckList::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	BackgroundImage->SetColorAndOpacity(DefaultBackgroundColor);
	DesiredFocusTarget = this;
}

void ULshPF_CharacterCheckList::WidgetConfirmAction()
{
	IsCharacterUse->SetFocus();
}

void ULshPF_CharacterCheckList::WidgetBackAction()
{
	ULshPF_FocusableWidgetBase* ParentWidget = GetTypedOuter<ULshPF_FocusableWidgetBase>();
	if (ParentWidget)
	{
		ParentWidget->RemoveFromParentStack();
	}
}

void ULshPF_CharacterCheckList::SetTargetCharacter(FName CharacterKey, FPlayerBattleCharacterInfo CharacterInfo)
{
	TargetCharacterKey = CharacterKey;
	IsCharacterUse->SetButtonText(CharacterInfo.CharacterName);
}

ULshPF_FocusableCheckBox* ULshPF_CharacterCheckList::GetIsCharacterUse() const
{
	return  IsCharacterUse;
}

TTuple<FName, TArray<FName>> ULshPF_CharacterCheckList::GetTargetCharacterInfo()
{
	TTuple<FName, TArray<FName>> Result;
	Result.Key = TargetCharacterKey;
	
	TArray<FName> AbilityKeys;
	TArray<UUserWidget*> AbilityCheckers = DynamicEntryBox_SkillSetting->GetAllEntries();

	for (UUserWidget* AbilityChecker : AbilityCheckers)
	{
		if (ULshPF_FocusableCheckBox* CheckBox = Cast<ULshPF_FocusableCheckBox>(AbilityChecker))
		{
			if (CheckBox->IsChecked())
			{
				AbilityKeys.Add(CheckBox->GetCheckBoxKey());
			}
		}
	}
	
	Result.Value = AbilityKeys;
	return Result;
}

bool ULshPF_CharacterCheckList::IsTargetCharacterUse() const
{
	return IsCharacterUse->IsChecked();
}

void ULshPF_CharacterCheckList::NativeConstruct()
{
	Super::NativeConstruct();

	DynamicEntryBox_SkillSetting->SetVisibility(ESlateVisibility::Hidden);
	
	DesiredFocusTarget = this;
	BP_BindChildWidgetGetFocus(IsCharacterUse);
	
	if (AbilityData)
	{
		TArray<FName> AbilityKeys = AbilityData->GetRowNames();
        
        for (FName AbilityKey : AbilityKeys)
        {
        	ULshPF_FocusableCheckBox* CheckBox = DynamicEntryBox_SkillSetting->CreateEntry<ULshPF_FocusableCheckBox>();
        	FLshPF_AbilityInfoTableRow* FindRow = AbilityData->FindRow<FLshPF_AbilityInfoTableRow>(AbilityKey, FString("AbilityKeyName Is Error"));
        	CheckBox->InitCheckBox(FindRow);
        	CheckBox->SetCheckBoxKey(AbilityKey);
        	BP_BindChildWidgetGetFocus(CheckBox);
        }
	}

	BackgroundImage->SetColorAndOpacity(DefaultBackgroundColor);

	IsCharacterUse->ChangedDelegate.BindLambda([this](bool IsChecked)
	{
		if (IsChecked)
		{
			DynamicEntryBox_SkillSetting->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			DynamicEntryBox_SkillSetting->SetVisibility(ESlateVisibility::Hidden);
		}
	});
}
