// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/LshPF_ActionBar.h"

#include "Components/DynamicEntryBox.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableButton.h"

void ULshPF_ActionBar::CreateActionBarEntry()
{
	ALshPF_PlayerControllerBase* PlayerController = Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer());
	
	for (const FActionBarEntry Entry : ActionBarEntry)
	{
		ULshPF_NotFocusableButton* CreatedButton = ActionBar->CreateEntry<ULshPF_NotFocusableButton>();
		CreatedButton->SetButtonText(Entry.EntryText);
		if (PlayerController)
		{
			CreatedButton->SetBindInputAction(Entry.EntryInputAction);
		}
	}
}

void ULshPF_ActionBar::NativeConstruct()
{
	Super::NativeConstruct();

	ALshPF_PlayerControllerBase* PlayerController = Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer());

	if (ShowDefaultConfirmAction)
	{
		ULshPF_NotFocusableButton* CreatedButton = ActionBar->CreateEntry<ULshPF_NotFocusableButton>();
		CreatedButton->SetButtonText(FText::FromString(TEXT("OK")));
		if (PlayerController)
		{
			CreatedButton->SetBindInputAction(PlayerController->GetDefaultConfirmAction());
		}
	}

	if (ShowDefaultBackAction)
	{
		ULshPF_NotFocusableButton* CreatedButton = ActionBar->CreateEntry<ULshPF_NotFocusableButton>();
		CreatedButton->SetButtonText(FText::FromString(TEXT("Back")));
		if (PlayerController)
		{
			CreatedButton->SetBindInputAction(PlayerController->GetDefaultBackAction());
		}
	}
}
