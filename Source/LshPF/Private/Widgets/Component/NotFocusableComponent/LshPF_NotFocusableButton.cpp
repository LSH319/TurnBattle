// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableButton.h"

#include "InputAction.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "Data/KeyTextureInfo.h"
#include "DeveloperSettings/LshPF_ImageSetting.h"
#include "Engine/AssetManager.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/LshPF_Button.h"

UButton* ULshPF_NotFocusableButton::GetButton()
{
	return ButtonWidget;
}

void ULshPF_NotFocusableButton::SetButtonText(FText Text)
{
	ButtonText->SetText(Text);
}

void ULshPF_NotFocusableButton::SetBindInputAction(UInputAction* InInputAction)
{
	BindInputAction.Reset();
	BindInputAction = InInputAction;

	InitImage();

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->InputDeviceChange.AddUObject(this, &ThisClass::RecentlyInputDeviceChangedCallback);
	}
}

void ULshPF_NotFocusableButton::InitImage()
{
	ALshPF_PlayerControllerBase* LshPF_PlayerController = GetLshPF_PlayerController();
	
	if (BindInputAction.IsValid())
	{
		TArray<FKey> BindKeys(LshPF_PlayerController->GetKeysByInputAction(BindInputAction.Get()));
		if (!BindKeys.IsEmpty())
		{
			const ULshPF_ImageSetting* LshPF_ImageSetting = GetDefault<ULshPF_ImageSetting>();
			for (FKey TargetKey : BindKeys)
			{
				TSoftObjectPtr<UKeyTextureInfo> KeyTextureSoftPtr = TargetKey.IsGamepadKey() ? LshPF_ImageSetting->GamepadImage : LshPF_ImageSetting->KeyboardMouseImage;
				
				UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
					KeyTextureSoftPtr.ToSoftObjectPath(),
					FStreamableDelegate::CreateLambda(
						[this, TargetKey, KeyTextureSoftPtr]
						{
							TSoftObjectPtr<UTexture2D> SoftTexture2D = KeyTextureSoftPtr.Get()->GetTextureByKey(TargetKey);
							CacheKeyImage(SoftTexture2D, TargetKey);
						}
					)
				);
			}
		}
	}
}

void ULshPF_NotFocusableButton::CacheKeyImage(TSoftObjectPtr<UTexture2D> CacheTarget, FKey InKey)
{
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		CacheTarget.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, InKey, CacheTarget]
			{
				if (InKey.IsGamepadKey())
				{
					CachedGamepadImage = CacheTarget.Get();
					ChangeImageWithInputDeviceType();
				}
				else
				{
					CachedKeyboardImage = CacheTarget.Get();
					ChangeImageWithInputDeviceType();
				}
			}
		)
	);
}

void ULshPF_NotFocusableButton::ChangeImageWithInputDeviceType()
{
	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		EInputDeviceType InputDeviceType = UISubsystem->GetRecentlyInputDeviceType();
		RecentlyInputDeviceChangedCallback(InputDeviceType);
	}
}

void ULshPF_NotFocusableButton::RecentlyInputDeviceChangedCallback(EInputDeviceType RecentlyInputDeviceType)
{
	switch (RecentlyInputDeviceType)
	{
		case EInputDeviceType::KeyboardAndMouse:
			if (CachedKeyboardImage)
			{
				ButtonImage->SetBrushFromTexture(CachedKeyboardImage);
			}
			break;
		case EInputDeviceType::Gamepad:
			if (CachedGamepadImage)
			{
				ButtonImage->SetBrushFromTexture(CachedGamepadImage);
			}
			break;
		default:
			break;
	}
}
