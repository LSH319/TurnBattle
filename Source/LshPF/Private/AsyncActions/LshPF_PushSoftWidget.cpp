// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/LshPF_PushSoftWidget.h"

#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

ULshPF_PushSoftWidget* ULshPF_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
                                                             APlayerController* OwningPlayerController, TSoftClassPtr<ULshPF_FocusableWidgetBase> InSoftWidgetClass,
                                                             FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("InSoftWidgetClass is null"));

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			ULshPF_PushSoftWidget* Node = NewObject<ULshPF_PushSoftWidget>();
			Node->CachedOwningWorld = World;
			Node->CachedOwningPC = OwningPlayerController;
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;
			
			return Node;
		}
	}

	return nullptr;
}

void ULshPF_PushSoftWidget::Activate()
{
	ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(CachedOwningWorld.Get());

	UISubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass,
		[this](ULshPF_FocusableWidgetBase* PushedWidget)
	{
		PushedWidget->SetOwningPlayer(CachedOwningPC.Get());
		if (bCachedFocusOnNewlyPushedWidget)
		{
			if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
			{
				WidgetToFocus->SetFocus();
			}
		}
		SetReadyToDestroy();
			
		AfterPush.Broadcast(PushedWidget);
	});
}
