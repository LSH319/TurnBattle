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

UWidget* ULshPF_PrimaryLayout::GetFocusTargetInFocusWidgetSwitcher()
{
	ULshPF_WidgetSwitcher* FocusWidgetSwitcher = FindFocusWidgetSwitcher();
	if (UWidget* FocusTargetWidget = GetFocusTargetInWidgetSwitcher(FocusWidgetSwitcher))
	{
		return FocusTargetWidget;
	}
	return nullptr;
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
	//추가된 요소를 역방향으로 순환하므로, 우선순위가 높은 Switcher를 나중에 Register 해야함
	if (!IsDesignTime())
	{
		if (!RegisterWidgetSwitcherMap.Contains(InStackTag))
		{
			TagPriorityArray.Add(InStackTag);
			RegisterWidgetSwitcherMap.Add(InStackTag, InSwitcher);
		}
	}
}

ULshPF_WidgetSwitcher* ULshPF_PrimaryLayout::FindFocusWidgetSwitcher()
{
	for (auto It = TagPriorityArray.rbegin(); It != TagPriorityArray.rend(); ++It)
	{
		const FGameplayTag& Tag = *It;
		ULshPF_WidgetSwitcher* LshPF_WidgetSwitcher = FindWidgetSwitcherByTag(Tag);
		if (LshPF_WidgetSwitcher->GetActiveWidget())
		{
			return LshPF_WidgetSwitcher;
		}
	}
	return nullptr;
}

UWidget* ULshPF_PrimaryLayout::GetFocusTargetInWidgetSwitcher(ULshPF_WidgetSwitcher* InWidgetSwitcher)
{
	if (InWidgetSwitcher)
	{
		if (ULshPF_FocusableWidgetBase* LshPF_FocusableWidgetBase = CastChecked<ULshPF_FocusableWidgetBase>(InWidgetSwitcher->GetActiveWidget()))
		{
			if (UWidget* FocusTargetWidget = LshPF_FocusableWidgetBase->GetDesiredFocusTarget())
			{
				return FocusTargetWidget;
			}
		}
	}
	return nullptr;
}

void ULshPF_PrimaryLayout::SetFocusToPriorityWidget()
{
	ULshPF_WidgetSwitcher* FocusWidgetSwitcher = FindFocusWidgetSwitcher();
	if (UWidget* FocusTargetWidget = GetFocusTargetInWidgetSwitcher(FocusWidgetSwitcher))
	{
		FocusTargetWidget->SetFocus();
	}
}
