#pragma once

#include "Widgets/Input/SButton.h"
#include "Input/Reply.h"

class LshPF_SButton : public SButton
{
public:
	//SButton 의 기능 사용을 위해 InnerButton 을 ARGUMENT로 사용 
	SLATE_BEGIN_ARGS(LshPF_SButton) : _InnerButton()
	{}
	SLATE_ARGUMENT(SButton::FArguments, InnerButton)
		
	SLATE_END_ARGS()
 
	void Construct(const FArguments& InArgs);
	
	//~ SWidget overrides
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;
	//~ SWidget

private:
	/**
	 * UISubsystem 에 InputDevice Update 요청
	 */
	void UpdateRecentlyInputDevice();
};
