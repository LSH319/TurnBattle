// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/LshPF_ListView.h"

#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

void ULshPF_ListView::WidgetBackAction()
{
	ULshPF_FocusableWidgetBase* ParentWidget = GetTypedOuter<ULshPF_FocusableWidgetBase>();
	if (ParentWidget)
	{
		ParentWidget->RemoveFromParentStack();
	}
}
