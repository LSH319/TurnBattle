// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/LshPF_PushConfirmScreen.h"

#include "Subsystems/LshPF_UISubsystem.h"

ULshPF_PushConfirmScreen* ULshPF_PushConfirmScreen::PushConfirmScreen(const UObject* WorldContextObject,
                                                                      TSoftClassPtr<ULshPF_ConfirmScreen> InConfirmScreenClass, EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			ULshPF_PushConfirmScreen* Node = NewObject<ULshPF_PushConfirmScreen>();
			Node->CachedOwningWorld = World;
			Node->CachedSoftWidgetClass = InConfirmScreenClass;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;

			return Node;
		}
	}

	return nullptr;
}

void ULshPF_PushConfirmScreen::Activate()
{
	ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(CachedOwningWorld.Get());

	UISubsystem->PushConfirmScreen(
		CachedSoftWidgetClass,
		CachedScreenType,
		CachedScreenTitle,
		CachedScreenMessage,
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			OnButtonClicked.Broadcast(ClickedButtonType);
			SetReadyToDestroy();
		}
	);
}
