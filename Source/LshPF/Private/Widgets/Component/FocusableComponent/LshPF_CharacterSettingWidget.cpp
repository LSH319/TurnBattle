// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_CharacterSettingWidget.h"

#include "LshPF_GameInstance.h"
#include "Components/DynamicEntryBox.h"
#include "Data/PlayerCharacterInfo.h"
#include "Widgets/Component/FocusableComponent/LshPF_CharacterCheckList.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableButton.h"

bool ULshPF_CharacterSettingWidget::SetPlayerCharacterInfoInInstance()
{
	TMap<FName, TArray<FName>> PlayerCharacterInfo;
	
	TArray<UUserWidget*> CharacterSettings = DynamicEntryBox_CharacterSetting->GetAllEntries();
	for (auto CharacterSetting : CharacterSettings)
	{// 각 위젯은 캐릭터 1개의 사용여부, 부여할 Ability 정보를 소유
		if (ULshPF_CharacterCheckList* CheckList = Cast<ULshPF_CharacterCheckList>(CharacterSetting))
		{
			if (CheckList->IsTargetCharacterUse())//캐릭터를 사용할 경우
			{
				//해당 위젯의 데이터를 받아 저장
				PlayerCharacterInfo.Add(CheckList->GetTargetCharacterInfo());
			}
		}
	}

	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	GameInstance->SetPlayerCharacterInfo(PlayerCharacterInfo);

	//사용 캐릭터가 없을경우 False 반환
	return !PlayerCharacterInfo.IsEmpty();
}

void ULshPF_CharacterSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	
	if (CharacterInfo)
	{
		for (auto Info : CharacterInfo->PlayerCharacterClassInfoMap)
		{//DA 의 캐릭터 데이터를 받아 위젯 생성
			ULshPF_CharacterCheckList* CharacterCheckList = DynamicEntryBox_CharacterSetting->CreateEntry<ULshPF_CharacterCheckList>();
			CharacterCheckList->SetTargetCharacter(Info.Key, Info.Value);
			CharacterCheckList->SetIsCharacterUse(GameInstance->GetPlayerCharacterInfo().Contains(Info.Key));
			BP_BindChildWidgetGetFocus(CharacterCheckList);
		}
	}

	BP_BindChildWidgetGetFocus(NextButton);
	NextButton->BackActionDelegate.BindLambda([this]()
	{
		RemoveFromParentStack();
	});
}

void ULshPF_CharacterSettingWidget::SetDesiredFocusTarget(ULshPF_FocusableWidgetBase* InFocusTargetWidget)
{
	Super::SetDesiredFocusTarget(InFocusTargetWidget);
	if (ULshPF_CharacterCheckList* BoxFocusTarget = Cast<ULshPF_CharacterCheckList>(InFocusTargetWidget))
	{
		DynamicEntryBoxFocusTarget = BoxFocusTarget;
	}
}
