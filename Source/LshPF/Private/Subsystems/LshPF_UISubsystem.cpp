// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/LshPF_UISubsystem.h"

#include "LshPF_GameplayTags.h"
#include "Engine/AssetManager.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputSettings.h"
#include "Widgets/LshPF_PrimaryLayout.h"
#include "Widgets/Component/LshPF_WidgetSwitcher.h"
#include "Widgets/Component/FocusableComponent/LshPF_ConfirmScreen.h"
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

void ULshPF_UISubsystem::PushConfirmScreen(TSoftClassPtr<ULshPF_ConfirmScreen> InConfirmScreenClass,
	EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg,
	TFunction<void(EButtonType)> ButtonClickedCallback)
{
	PushSoftWidgetToStackAsync(
		LshPF_GameplayTags::LshPF_WidgetStack_Test2,//todo : Test용 태그, 변경 필요
		InConfirmScreenClass,
		[InScreenType, InScreenTitle, InScreenMsg, ButtonClickedCallback](ULshPF_FocusableWidgetBase* PushedWidget)
		{
			if (ULshPF_ConfirmScreen* ConfirmScreen = dynamic_cast<ULshPF_ConfirmScreen*>(PushedWidget))
			{
				ConfirmScreen->InitConfirmScreen(InScreenType, InScreenTitle, InScreenMsg, ButtonClickedCallback);
				ConfirmScreen->SetFocus();
			}
		}
	);
}

EInputDeviceType ULshPF_UISubsystem::GetRecentlyInputDeviceType()
{
	return RecentlyInputDeviceType;
}

void ULshPF_UISubsystem::SetRecentlyInputDeviceType(EInputDeviceType InRecentlyInputDeviceType)
{
	if (RecentlyInputDeviceType != InRecentlyInputDeviceType)
	{//InputDevice 가 변경된 경우에만 Broadcast
		RecentlyInputDeviceType = InRecentlyInputDeviceType;
		InputDeviceChange.Broadcast(RecentlyInputDeviceType);
	}
}

void ULshPF_UISubsystem::SetRecentlyInputDeviceType()
{
	FHardwareDeviceIdentifier HardwareDeviceIdentifier = UInputDeviceSubsystem::Get()->GetMostRecentlyUsedHardwareDevice(GetGameInstance()->GetPrimaryPlayerController()->GetPlatformUserId());

	switch(HardwareDeviceIdentifier.PrimaryDeviceType)
	{
		case EHardwareDevicePrimaryType::KeyboardAndMouse:
			SetRecentlyInputDeviceType(EInputDeviceType::KeyboardAndMouse);
			break;
		case EHardwareDevicePrimaryType::Gamepad:
			SetRecentlyInputDeviceType(EInputDeviceType::Gamepad);
			break;
		default:
			break;
	}
}

UWidget* ULshPF_UISubsystem::GetFocusTargetWidget()
{
	return CreatedPrimaryLayout->GetFocusTargetInFocusWidgetSwitcher();
} 