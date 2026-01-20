// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/LshPF_Button.h"

#include "Components/ButtonSlot.h"
#include "Widgets/SlateWidgets/LshPF_SButton.h"

TSharedRef<SWidget> ULshPF_Button::RebuildWidget()
{
	//Slate Widget 을 커스텀하여 사용하기 위한 override
	//기본 기능을 사용하기 위해 SButton 의 Arguments 를 전달
PRAGMA_DISABLE_DEPRECATION_WARNINGS
	SButton::FArguments ButtonArgs = SButton::FArguments()
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
		.OnHovered_UObject( this, &ThisClass::SlateHandleHovered )
		.OnUnhovered_UObject( this, &ThisClass::SlateHandleUnhovered )
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.PressMethod(PressMethod)
		.IsFocusable(IsFocusable)
		;
	MyButton = SNew(LshPF_SButton)
		.InnerButton(ButtonArgs);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
		if ( GetChildrenCount() > 0 )
		{
			Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
		}
	
	return MyButton.ToSharedRef();
}
