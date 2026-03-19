// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_CharacterSettingWidget.h"

#include "LshPF_GameInstance.h"
#include "Components/DynamicEntryBox.h"
#include "Data/PlayerCharacterInfo.h"
#include "Widgets/Component/FocusableComponent/LshPF_CharacterCheckList.h"

bool ULshPF_CharacterSettingWidget::SetPlayerCharacterInfoInInstance()
{
	TMap<FName, TArray<FName>> PlayerCharacterInfo;
	
	TArray<UUserWidget*> CharacterSettings = DynamicEntryBox_CharacterSetting->GetAllEntries();
	for (auto CharacterSetting : CharacterSettings)
	{
		if (ULshPF_CharacterCheckList* CheckList = Cast<ULshPF_CharacterCheckList>(CharacterSetting))
		{
			if (CheckList->IsTargetCharacterUse())
			{
				PlayerCharacterInfo.Add(CheckList->GetTargetCharacterInfo());
			}
		}
	}

	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	GameInstance->SetPlayerCharacterInfo(PlayerCharacterInfo);

	return !PlayerCharacterInfo.IsEmpty();
}

void ULshPF_CharacterSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CharacterInfo)
	{
		for (auto Info : CharacterInfo->PlayerCharacterClassInfoMap)
		{
			ULshPF_CharacterCheckList* CharacterCheckList = DynamicEntryBox_CharacterSetting->CreateEntry<ULshPF_CharacterCheckList>();
			CharacterCheckList->SetTargetCharacter(Info.Key, Info.Value);
			BP_BindChildWidgetGetFocus(CharacterCheckList);
		}
	}
}
