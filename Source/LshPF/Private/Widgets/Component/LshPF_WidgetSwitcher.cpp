// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/LshPF_WidgetSwitcher.h"

#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

ULshPF_FocusableWidgetBase* ULshPF_WidgetSwitcher::AddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass)
{
	return NativeAddWidgetToStack(InSoftWidgetClass);
}

ULshPF_FocusableWidgetBase* ULshPF_WidgetSwitcher::NativeAddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass)
{
	if (GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(ULshPF_WidgetSwitcher, BP_AddWidgetToStack)))
	{//BP_AddWidgetToStack 가 블루프린트에서 로직을 설정한 경우 해당 함수 호출
		return BP_AddWidgetToStack(InSoftWidgetClass);
	}
	else
	{
		ULshPF_FocusableWidgetBase* CreatedWidget = CreateWidget<ULshPF_FocusableWidgetBase>(GetOwningPlayer(), InSoftWidgetClass.Get());
		AddChild(CreatedWidget);
		SetActiveWidget(CreatedWidget);
		CreatedWidget->OnWidgetDestroyed.BindUObject(this, &ThisClass::ChildWidgetDestroyed);
				
		return CreatedWidget;
	}
}

void ULshPF_WidgetSwitcher::ChildWidgetDestroyed(int32 ChildIndex)
{
	if (GetActiveWidgetIndex() == ChildIndex)
	{
		SetActiveWidgetIndex(ChildIndex - 1);
	}
}
