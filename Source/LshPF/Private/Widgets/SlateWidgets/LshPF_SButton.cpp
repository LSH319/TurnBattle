#include "Widgets/SlateWidgets/LshPF_SButton.h"

#include "Subsystems/LshPF_UISubsystem.h"

void LshPF_SButton::Construct(const FArguments& InArgs)
{
	SButton::Construct(InArgs._InnerButton);
}

FReply LshPF_SButton::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	//키 입력을 Enhanced Input 까지 넘기기 위해 Unhandled 를 return 하도록 Override
	EUINavigation UINavigationAction = FSlateApplication::Get().GetNavigationDirectionFromKey(InKeyEvent);
	if (UINavigationAction == EUINavigation::Left ||
		UINavigationAction == EUINavigation::Right ||
		UINavigationAction == EUINavigation::Up ||
		UINavigationAction == EUINavigation::Down)
	{
		//UINavigation 에 할당된 버튼 입력시 InputDevice Update 요청
		UpdateRecentlyInputDevice();
	}
	
	return FReply::Unhandled();
}

FReply LshPF_SButton::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	//키 입력을 Enhanced Input 까지 넘기기 위해 Unhandled 를 return 하도록 Override
	return FReply::Unhandled();
}

FReply LshPF_SButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//마우스 버튼 Down 시 InputDevice Update 요청, 버튼의 기본 동작을 하도록 SButton 의 함수 호출 
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
		if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(World))
		{
			UISubsystem->SetRecentlyInputDeviceType();
		}
	}
}
