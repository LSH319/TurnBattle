#include "Widgets/SlateWidgets/LshPF_SButton.h"

void LshPF_SButton::Construct(const FArguments& InArgs)
{
	SButton::Construct(InArgs._InnerButton);
	/*
	UButton 의 RebuildWidget override, 해당 함수에서 아래 코드 활용
	
	SButton::FArguments ButtonArgs = SButton::FArguments()
	.OnClicked(...)
	// 나머지 설정
	
	SNew(SMyButton)
		.InnerButton(ButtonArgs);
		
	 */
}

FReply LshPF_SButton::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Unhandled();
	// FSlateApplication::Get().GetNavigationActionFromKey(InKeyEvent) == EUINavigationAction::Accept 조건식 수정
	/*FReply Reply = FReply::Unhandled();
	if (IsEnabled() && FSlateApplication::Get().GetNavigationActionFromKey(InKeyEvent) == EUINavigationAction::Accept)
	{
		bIsPressedLocal = true;
		Press();

		if (PressMethod == EButtonPressMethod::ButtonPress)
		{
			//execute our "OnClicked" delegate, and get the reply
			Reply = ExecuteOnClick();

			//You should ALWAYS handle the OnClicked event.
			ensure(Reply.IsEventHandled() == true);
		}
		else
		{
			Reply = FReply::Handled();
		}
	}
	else
	{
		Reply = SBorder::OnKeyDown(MyGeometry, InKeyEvent);
	}

	//return the constructed reply
	return Reply;*/
}

FReply LshPF_SButton::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Unhandled();
	// FSlateApplication::Get().GetNavigationActionFromKey(InKeyEvent) == EUINavigationAction::Accept 조건식 수정
	/*FReply Reply = FReply::Unhandled();
	if (IsEnabled() && FSlateApplication::Get().GetNavigationActionFromKey(InKeyEvent) == EUINavigationAction::Accept)
	{
		const bool bWasPressed = bIsPressedLocal;

		Release();

		//@Todo Slate: This should check focus, however we don't have that API yet, will be easier when focus is unified.
		if ( PressMethod == EButtonPressMethod::ButtonRelease || ( PressMethod == EButtonPressMethod::DownAndUp && bWasPressed ) )
		{
			//execute our "OnClicked" delegate, and get the reply
			Reply = ExecuteOnClick();

			//You should ALWAYS handle the OnClicked event.
			ensure(Reply.IsEventHandled() == true);
		}
		else
		{
			Reply = FReply::Handled();
		}
		
		bIsPressedLocal = false;
	}

	//return the constructed reply
	return Reply;*/
}
