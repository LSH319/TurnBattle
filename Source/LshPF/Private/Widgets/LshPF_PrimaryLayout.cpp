// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LshPF_PrimaryLayout.h"

#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/LshPF_WidgetSwitcher.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

ULshPF_WidgetSwitcher* ULshPF_PrimaryLayout::FindWidgetSwitcherByTag(const FGameplayTag InTag)
{
	checkf(RegisterWidgetSwitcherMap.Contains(InTag), TEXT("Can not find Switcher by tag %s"), *InTag.ToString());
	
	return RegisterWidgetSwitcherMap.FindRef(InTag);
}

void ULshPF_PrimaryLayout::NativeConstruct()
{
	Super::NativeConstruct();

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->FindNewFocusWidget.BindUObject(this, &ThisClass::SetFocusToPriorityWidget);
	}
}

void ULshPF_PrimaryLayout::RegisterWidgetSwitcher(FGameplayTag InStackTag, ULshPF_WidgetSwitcher* InSwitcher)
{
	if (!IsDesignTime())
	{
		if (!RegisterWidgetSwitcherMap.Contains(InStackTag))
		{
			TagPriorityArray.Add(InStackTag);
			RegisterWidgetSwitcherMap.Add(InStackTag, InSwitcher);
		}
	}
}

void ULshPF_PrimaryLayout::SetFocusToPriorityWidget()
{
	for (auto It = TagPriorityArray.rbegin(); It != TagPriorityArray.rend(); ++It)
	{
		const FGameplayTag& Tag = *It;
		ULshPF_WidgetSwitcher* LshPF_WidgetSwitcher = FindWidgetSwitcherByTag(Tag);
		if (UWidget* ActiveWidget = LshPF_WidgetSwitcher->GetActiveWidget())
		{
			if (ULshPF_FocusableWidgetBase* LshPF_FocusableWidgetBase = CastChecked<ULshPF_FocusableWidgetBase>(ActiveWidget))
			{
				if (LshPF_FocusableWidgetBase->IsFocusable())
				{
					if (UWidget* WidgetToFocus = LshPF_FocusableWidgetBase->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
						break;
					}
				}
			}
		}
	}
}
