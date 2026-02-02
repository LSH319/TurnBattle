// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_ConfirmScreen.h"

#include "InputAction.h"
#include "Components/Button.h"
#include "Components/DynamicEntryBox.h"
#include "Components/TextBlock.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableButton.h"

void ULshPF_ConfirmScreen::InitConfirmScreen(EConfirmScreenType InScreenType, const FText& InScreenTitle,
                                             const FText& InScreenMsg, TFunction<void(EButtonType)> ButtonClickedCallback)
{
	TextBlock_Title->SetText(InScreenTitle);
	TextBlock_Message->SetText(InScreenMsg);
	
	//필요한 데이터 저장
	CachedCallbackFunction = ButtonClickedCallback;
	CachedConfirmScreenType = InScreenType;
	
	//이미 생성되어 있는 버튼이 있으면 리셋
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{	
		DynamicEntryBox_Buttons->Reset();
	}
	
	ALshPF_PlayerControllerBase* LshPF_PlayerController = Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer());

	switch (InScreenType)
	{
		case EConfirmScreenType::Ok:
			{//버튼 생성 로직
				ULshPF_NotFocusableButton* OkButton = DynamicEntryBox_Buttons->CreateEntry<ULshPF_NotFocusableButton>();
				OkButton->SetButtonText(FText::FromString(TEXT("OK")));
				if (LshPF_PlayerController)
				{
					OkButton->SetBindInputAction(LshPF_PlayerController->GetDefaultConfirmAction());
				}
				OkButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::ButtonClickedCallback_Yes);
				break;
			}
		case EConfirmScreenType::YesNo:
			{//버튼 생성 로직
				ULshPF_NotFocusableButton* YesButton = DynamicEntryBox_Buttons->CreateEntry<ULshPF_NotFocusableButton>();
				YesButton->SetButtonText(FText::FromString(TEXT("YES")));
				if (LshPF_PlayerController)
				{
					YesButton->SetBindInputAction(LshPF_PlayerController->GetDefaultConfirmAction());
				}
				YesButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::ButtonClickedCallback_Yes);

				ULshPF_NotFocusableButton* NoButton = DynamicEntryBox_Buttons->CreateEntry<ULshPF_NotFocusableButton>();
				NoButton->SetButtonText(FText::FromString(TEXT("NO")));
				if (LshPF_PlayerController)
				{
					NoButton->SetBindInputAction(LshPF_PlayerController->GetDefaultBackAction());
				}
				NoButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::ButtonClickedCallback_No);

				break;
			}
		case EConfirmScreenType::Unknown:
		default:
			break;
	}
}

void ULshPF_ConfirmScreen::WidgetConfirmAction()
{
	ButtonClickedCallback_Yes();
}

void ULshPF_ConfirmScreen::WidgetBackAction()
{
	ButtonClickedCallback_No();
}

void ULshPF_ConfirmScreen::ButtonClickedCallback_Yes()
{
	CachedCallbackFunction(EButtonType::OkOrYes);
	RemoveFromParentStack();
}

void ULshPF_ConfirmScreen::ButtonClickedCallback_No()
{
	//EConfirmScreenType 에 따라 반환값 설정을 위한 코드
	switch (CachedConfirmScreenType)
	{
		case EConfirmScreenType::Ok:
			CachedCallbackFunction(EButtonType::OkOrYes);
			break;
		case EConfirmScreenType::YesNo:
			CachedCallbackFunction(EButtonType::No);
			break;
		case EConfirmScreenType::Unknown:
		default:
			break;
	}
	
	RemoveFromParentStack();
}
