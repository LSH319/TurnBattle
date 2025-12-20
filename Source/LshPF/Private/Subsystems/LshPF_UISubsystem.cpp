// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/LshPF_UISubsystem.h"

#include "Engine/AssetManager.h"
#include "Widgets/LshPF_PrimaryLayout.h"
#include "Widgets/Component/LshPF_WidgetSwitcher.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

ULshPF_UISubsystem* ULshPF_UISubsystem::Get(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
		return UGameInstance::GetSubsystem<ULshPF_UISubsystem>(World->GetGameInstance());
	}
	return nullptr;
}

void ULshPF_UISubsystem::RegisterCreatedPrimaryLayoutWidget(ULshPF_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);
	CreatedPrimaryLayout = InCreatedWidget;
}

void ULshPF_UISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
	TSoftClassPtr<ULshPF_FocusableWidgetBase> InSoftWidgetClass,
	TFunction<void(ULshPF_FocusableWidgetBase*)> AsyncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
	FStreamableDelegate::CreateLambda(
	[this, InWidgetStackTag, InSoftWidgetClass, AsyncPushStateCallback]()
			{
				TSoftClassPtr<ULshPF_FocusableWidgetBase> LoadedWidgetClass = InSoftWidgetClass.Get();
				TSoftClassPtr<ULshPF_FocusableWidgetBase>& SoftLoadedWidgetClass = LoadedWidgetClass;
		
				check(SoftLoadedWidgetClass && CreatedPrimaryLayout);

				ULshPF_WidgetSwitcher* FoundWidgetStack = CreatedPrimaryLayout->FindWidgetSwitcherByTag(InWidgetStackTag);
				ULshPF_FocusableWidgetBase* CreatedWidget = FoundWidgetStack->AddWidgetToStack(SoftLoadedWidgetClass);
				
				AsyncPushStateCallback(CreatedWidget);
			}
		)
	);
} 