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

bool ULshPF_NotFocusableButton::SetInputActionTag(FGameplayTag InFGameplayTag)
{
	InputActionTag = InFGameplayTag;

	const bool IsInitSuccess = InitImage();
	
	if (IsInitSuccess)
	{
		if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
		{
			//UISubsystem 에서 InputDevice 변경시 호출하는 delegate
			UISubsystem->InputDeviceChange.AddUObject(this, &ThisClass::RecentlyInputDeviceChangedCallback);
		}
	}
	
	return IsInitSuccess;
}

void ULshPF_NotFocusableButton::BindClickEvent()
{
	//다중 바인딩 방지를 위한 Remove
	ButtonWidget->OnClicked.RemoveAll(this);
	ButtonWidget->OnClicked.AddDynamic(this, &ThisClass::RequestExecuteInputActionToController);
}

void ULshPF_NotFocusableButton::RequestExecuteInputActionToController()
{
	if (ALshPF_PlayerControllerBase* PlayerController = Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer()))
	{
		PlayerController->ExecuteInputActionByGameplayTag(InputActionTag);
	}
}

UInputAction* ULshPF_NotFocusableButton::GetInputActionByTag() const
{
	if (ALshPF_PlayerControllerBase* PlayerController = Cast<ALshPF_PlayerControllerBase>(GetOwningPlayer()))
	{
		return PlayerController->GetInputActionByGameplayTag(InputActionTag);
	}
	return nullptr;
}

bool ULshPF_NotFocusableButton::InitImage()
{
	ALshPF_PlayerControllerBase* LshPF_PlayerController = GetLshPF_PlayerController();

	//사용할 값이 잘못된 경우 false
	if (GetInputActionByTag() && LshPF_PlayerController)
	{
		//IA 에 바인딩 된 Keys
		TArray<FKey> BindKeys(LshPF_PlayerController->GetKeysByInputAction(GetInputActionByTag()));
		//IMC ADD 가 늦거나 등록이 안된경우 false
		if (!BindKeys.IsEmpty())
		{
			//UDeveloperSettings 을 상속한 세팅
			const ULshPF_ImageSetting* LshPF_ImageSetting = GetDefault<ULshPF_ImageSetting>();
			for (FKey TargetKey : BindKeys)
			{
				TSoftObjectPtr<UKeyTextureInfo> KeyTextureSoftPtr = TargetKey.IsGamepadKey() ? LshPF_ImageSetting->GamepadImage : LshPF_ImageSetting->KeyboardMouseImage;

				//UKeyTextureInfo 가 SoftObjectPtr 이므로 Load 후 처리를 위한 함수
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
			//Load 후 이벤트 등록을 완료했으므로 true
			return true;
		}
	}
	return false;
}

void ULshPF_NotFocusableButton::CacheKeyImage(TSoftObjectPtr<UTexture2D> CacheTarget, FKey InKey)
{
	//CacheTarget 이 SoftObjectPtr 이므로 Load 후 처리를 위한 함수
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		CacheTarget.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, InKey, CacheTarget]
			{
				//InKey 의 Type 에 따라 올바른 변수에 저장
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
