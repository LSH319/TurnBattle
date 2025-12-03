// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LshPF_PrimaryLayout.h"

ULshPF_WidgetSwitcher* ULshPF_PrimaryLayout::FindWidgetSwitcherByTag(const FGameplayTag InTag)
{
	checkf(RegisterWidgetSwitcherMap.Contains(InTag), TEXT("Can not find Switcher by tag %s"), *InTag.ToString());
	
	return RegisterWidgetSwitcherMap.FindRef(InTag);
}

void ULshPF_PrimaryLayout::RegisterWidgetSwitcher(FGameplayTag InStackTag, ULshPF_WidgetSwitcher* InSwitcher)
{
	if (!IsDesignTime())
	{
		if (!RegisterWidgetSwitcherMap.Contains(InStackTag))
		{
			RegisterWidgetSwitcherMap.Add(InStackTag, InSwitcher);
		}
	}
}
