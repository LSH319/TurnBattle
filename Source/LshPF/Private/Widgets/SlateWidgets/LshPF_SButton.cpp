#include "Widgets/SlateWidgets/LshPF_SButton.h"

#include "GameFramework/InputDeviceSubsystem.h"

void LshPF_SButton::Construct(const FArguments& InArgs)
{
	SButton::Construct(InArgs._InnerButton);
}

FReply LshPF_SButton::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	EUINavigation UINavigationAction = FSlateApplication::Get().GetNavigationDirectionFromKey(InKeyEvent);
	if (UINavigationAction == EUINavigation::Left ||
		UINavigationAction == EUINavigation::Right ||
		UINavigationAction == EUINavigation::Up ||
		UINavigationAction == EUINavigation::Down)
	{
		UWorld* World = nullptr;
		if (GEngine && GEngine->GameViewport)
		{
			World = GEngine->GameViewport->GetWorld();
		}
		if (World)
		{
			APlayerController* PC = World->GetFirstPlayerController();
			FHardwareDeviceIdentifier HardwareDeviceIdentifier = UInputDeviceSubsystem::Get()->GetMostRecentlyUsedHardwareDevice(PC->GetPlatformUserId());
	        FString Device = HardwareDeviceIdentifier.PrimaryDeviceType == EHardwareDevicePrimaryType::KeyboardAndMouse ? "KeyboardAndMouse" : "Gamepad";
		}
	}
	
	return FReply::Unhandled();
}

FReply LshPF_SButton::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Unhandled();
}