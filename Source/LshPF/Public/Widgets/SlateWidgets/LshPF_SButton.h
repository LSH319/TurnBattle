#pragma once

#include "Widgets/Input/SButton.h"
#include "Input/Reply.h"

class LshPF_SButton : public SButton
{
public:
	SLATE_BEGIN_ARGS(LshPF_SButton) : _InnerButton()
	{}
	SLATE_ARGUMENT(SButton::FArguments, InnerButton)
		
	SLATE_END_ARGS()
 
	void Construct(const FArguments& InArgs);
	
	//~ SWidget overrides
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	//~ SWidget
};
