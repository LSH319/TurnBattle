// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_ConfirmScreen.h"

#include "Components/DynamicEntryBox.h"
#include "Components/TextBlock.h"

void ULshPF_ConfirmScreen::InitConfirmScreen(EConfirmScreenType InScreenType, const FText& InScreenTitle,
                                             const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	TextBlock_Title->SetText(InScreenTitle);
	TextBlock_Message->SetText(InScreenMsg);

	//이미 생성되어 있는 버튼이 있으면 리셋
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{	
		DynamicEntryBox_Buttons->Reset();
	}

	switch (InScreenType)
	{
		case EConfirmScreenType::Ok:
		case EConfirmScreenType::YesNo:
		case EConfirmScreenType::Unknown:
		default:
			break;
	}
}
