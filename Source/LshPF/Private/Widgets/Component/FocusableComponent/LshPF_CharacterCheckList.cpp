// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_CharacterCheckList.h"

#include "LshPF_GameInstance.h"
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
	//내부 체크박스 위젯으로 포커스 이동
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

	if (AbilityData)
	{
		TArray<FName> AbilityKeys = AbilityData->GetRowNames();
        
		for (FName AbilityKey : AbilityKeys)
		{//DT 의 RowNames 에 따라 위젯 생성
			ULshPF_FocusableCheckBox* CheckBox = DynamicEntryBox_SkillSetting->CreateEntry<ULshPF_FocusableCheckBox>();
			FLshPF_AbilityInfoTableRow* FindRow = AbilityData->FindRow<FLshPF_AbilityInfoTableRow>(AbilityKey, FString("AbilityKeyName Is Error"));
			CheckBox->InitCheckBox(FindRow);
			CheckBox->SetCheckBoxKey(AbilityKey);
			CheckBox->SetIsCheck(AbilityIsUseInInstance(AbilityKey));
			BP_BindChildWidgetGetFocus(CheckBox);
		}
	}
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
	{//각 스킬 사용 여부에 따른 위젯들
		if (ULshPF_FocusableCheckBox* CheckBox = Cast<ULshPF_FocusableCheckBox>(AbilityChecker))
		{//Cast 해여 확인
			if (CheckBox->IsChecked())
			{//사용으로 설정되어 있을경우 배열에 추가
				AbilityKeys.Add(CheckBox->GetCheckBoxKey());
			}
		}
	}
	//취합된 배열로 Value 설정 후 반환
	Result.Value = AbilityKeys;
	return Result;
}

bool ULshPF_CharacterCheckList::IsTargetCharacterUse() const
{
	return IsCharacterUse->IsChecked();
}

void ULshPF_CharacterCheckList::SetIsCharacterUse(bool InIsCharacterUse)
{
	IsCharacterUse->SetIsCheck(InIsCharacterUse);
}

void ULshPF_CharacterCheckList::NativeConstruct()
{
	Super::NativeConstruct();

	IsCharacterUse->ChangedDelegate.BindLambda([this](bool IsChecked)
	{//캐릭터를 사용하지 않을 경우 DynamicEntryBox 설정을 변경하여 체크하지 못하도록 설정
		if (IsChecked)
		{
			DynamicEntryBox_SkillSetting->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			DynamicEntryBox_SkillSetting->SetVisibility(ESlateVisibility::Hidden);
		}
	});
	
	DynamicEntryBox_SkillSetting->SetVisibility(ESlateVisibility::Hidden);
	
	DesiredFocusTarget = this;
	BP_BindChildWidgetGetFocus(IsCharacterUse);

	BackgroundImage->SetColorAndOpacity(DefaultBackgroundColor);
}

bool ULshPF_CharacterCheckList::AbilityIsUseInInstance(FName InAbilityKey)
{
	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	TMap<FName, TArray<FName>> CharacterInfo = GameInstance->GetPlayerCharacterInfo();

	if (CharacterInfo.Contains(TargetCharacterKey))
	{//관리하는 캐릭터가 사용 캐릭터에 포함되어있는지 확인
		for (FName UseAbilityKey : CharacterInfo[TargetCharacterKey])
		{//사용할 경우 InAbilityKey 를 사용하는지 체크
			if (UseAbilityKey == InAbilityKey) return true;//사용할 경우 true
		}
	}
	//캐릭터 미사용 || 해당 어빌리티 미사용시 false
	return false;
}
