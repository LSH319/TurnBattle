// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/ListEntries/LshPF_AbilityListEntry.h"

#include "Ability/LshPF_Ability.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULshPF_AbilityListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);

	InitListEntryData(CastChecked<ULshPF_Ability>(ListItemObject));
}

void ULshPF_AbilityListEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	Super::NativeOnItemSelectionChanged(bIsSelected);

	if (bIsSelected)
	{
		Background->SetBrush(OnFocusBackgroundBrush);
	}
	else
	{
		Background->SetBrush(DefaultBackgroundBrush);
	}
}

void ULshPF_AbilityListEntry::InitListEntryData(ULshPF_Ability* AbilityData)
{
	TextBlock_AbilityName->SetText(AbilityData->GetAbilityName());
	TextBlock_CostType->SetText(FText::FromString(AbilityData->GetCostAttributeType()));
	FString StringCost = FString::SanitizeFloat(AbilityData->GetAbilityCost());
	TextBlock_Cost->SetText(FText::FromString(StringCost));
}

void ULshPF_AbilityListEntry::NativePreConstruct()
{
	Super::NativePreConstruct();
	Background->SetBrush(DefaultBackgroundBrush);
}

FText ULshPF_AbilityListEntry::GetDescriptionText(ULshPF_Ability* AbilityData)
{
	return FText::FromString(AbilityData->GetDescription());
}
