// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/LshPF_ActionBar.h"

#include "LshPF_GameplayTags.h"
#include "Components/DynamicEntryBox.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableButton.h"

bool ULshPF_ActionBar::CreateActionBarEntry()
{
	ALshPF_PlayerControllerBase* PlayerController = Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer());
	bool IsSuccess = true;
	ActionBar->Reset();

	IsSuccess = IsSuccess && CreateDefaultEntry();
	for (const FActionBarEntry Entry : ActionBarEntry)
	{
		ULshPF_NotFocusableButton* CreatedButton = ActionBar->CreateEntry<ULshPF_NotFocusableButton>();
		CreatedButton->SetButtonText(Entry.EntryText);

		if (PlayerController)
		{
			//SetBindInputAction 실행 중 false 가 있을경우 false return
			IsSuccess = IsSuccess && CreatedButton->SetInputActionTag(Entry.InputActionTag);

			if (Entry.IsNeedBindClick)
			{
				CreatedButton->BindClickEvent();
			}
		}
	}

	return IsSuccess;
}

void ULshPF_ActionBar::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	
	bool IsSuccess = CreateActionBarEntry();
	if (!IsSuccess)
	{
		GetWorld()->GetTimerManager().SetTimer(
        	TimerHandle,
        	FTimerDelegate::CreateLambda([this]()
        		{
			        if (bool ReTrySuccess = CreateActionBarEntry())
        			{
			        	SetVisibility(ESlateVisibility::Visible);
        				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
        			}
        		}),
        	0.1f,
        	true);
	}
	
	//CreateDefaultEntry();
}

bool ULshPF_ActionBar::CreateDefaultEntry()
{
	ALshPF_PlayerControllerBase* PlayerController = Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer());
	bool IsSuccess = true;
	if (ShowDefaultConfirmAction)
	{
		ULshPF_NotFocusableButton* CreatedButton = ActionBar->CreateEntry<ULshPF_NotFocusableButton>();
		CreatedButton->SetButtonText(FText::FromString(TEXT("OK")));
		if (PlayerController)
		{
			IsSuccess = IsSuccess && CreatedButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultConfirm);
			CreatedButton->BindClickEvent();
		}
	}

	if (ShowDefaultBackAction)
	{
		ULshPF_NotFocusableButton* CreatedButton = ActionBar->CreateEntry<ULshPF_NotFocusableButton>();
		CreatedButton->SetButtonText(FText::FromString(TEXT("Back")));
		if (PlayerController)
		{
			IsSuccess = IsSuccess && CreatedButton->SetInputActionTag(LshPF_GameplayTags::LshPF_InputAction_DefaultBack);
			CreatedButton->BindClickEvent();
		}
	}

	return IsSuccess;
}
