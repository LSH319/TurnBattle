// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_ConfirmScreen.h"

#include "InputAction.h"
#include "LshPF_GameplayTags.h"
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
				bool IsSuccess = true;
				ULshPF_NotFocusableButton* OkButton = DynamicEntryBox_Buttons->CreateEntry<ULshPF_NotFocusableButton>();
				OkButton->SetButtonText(FText::FromString(TEXT("OK")));
				if (LshPF_PlayerController)
				{
					IsSuccess = IsSuccess && OkButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultConfirm);
					
					if (!IsSuccess)
					{
						GetWorld()->GetTimerManager().SetTimer(
							TimerHandle,
							FTimerDelegate::CreateLambda([this, OkButton]()
								{
								UE_LOG(LogTemp, Warning, TEXT("InitConfirmScreen"));	
									if (bool ReTrySuccess = OkButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultConfirm))
									{
										GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
										GetDesiredFocusTarget()->SetFocus();
									}
								}),
							0.1f,
							true);
					}
				}
				OkButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::ButtonClickedCallback_Yes);
				break;
			}
		case EConfirmScreenType::YesNo:
			{//버튼 생성 로직
				bool IsSuccess = true;
				ULshPF_NotFocusableButton* YesButton = DynamicEntryBox_Buttons->CreateEntry<ULshPF_NotFocusableButton>();
				YesButton->SetButtonText(FText::FromString(TEXT("YES")));
				if (LshPF_PlayerController)
				{
					IsSuccess = IsSuccess && YesButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultConfirm);
				}
				YesButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::ButtonClickedCallback_Yes);

				ULshPF_NotFocusableButton* NoButton = DynamicEntryBox_Buttons->CreateEntry<ULshPF_NotFocusableButton>();
				NoButton->SetButtonText(FText::FromString(TEXT("NO")));
				if (LshPF_PlayerController)
				{
					IsSuccess = IsSuccess && NoButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultBack);
				}
				NoButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::ButtonClickedCallback_No);
				if (!IsSuccess)
				{
					GetWorld()->GetTimerManager().SetTimer(
						TimerHandle,
						FTimerDelegate::CreateLambda([this, YesButton, NoButton]()
							{
								bool ReTrySuccess = true;
								ReTrySuccess = ReTrySuccess && YesButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultConfirm);
								ReTrySuccess = ReTrySuccess && NoButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultBack);
								if (ReTrySuccess)
								{
									GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
									GetDesiredFocusTarget()->SetFocus();
								}
							}),
						0.1f,
						true);
				}
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
