#include "Widgets/SlateWidgets/LshPF_SButton.h"

#include "GameFramework/InputDeviceSubsystem.h"
#include "Subsystems/LshPF_UISubsystem.h"

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
		UpdateRecentlyInputDevice();
	}
	
	return FReply::Unhandled();
}

FReply LshPF_SButton::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Unhandled();
}

FReply LshPF_SButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	UpdateRecentlyInputDevice();
	return SButton::OnMouseButtonDown(MyGeometry, MouseEvent);
}

void LshPF_SButton::UpdateRecentlyInputDevice()
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
		if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(World))
		{
			UISubsystem->SetRecentlyInputDeviceType(HardwareDeviceIdentifier.PrimaryDeviceType);
		}
	}
}
