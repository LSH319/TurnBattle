// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/ListEntries/LshPF_AbilityListEntry.h"

#include "Ability/LshPF_Ability.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Subsystems/LshPF_UISubsystem.h"

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
		if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
		{
			UISubsystem->OnButtonDescriptionTextUpdated.Broadcast(DescriptionText);
		}
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
	int32 CostValue = FMath::TruncToInt(AbilityData->GetAbilityCost());
	TextBlock_Cost->SetText(FText::AsNumber(CostValue));

	if (AbilityData->IsCanActivate())
	{
		TextBlock_AbilityName->SetColorAndOpacity(AvailableTextColor);
		TextBlock_CostType->SetColorAndOpacity(AvailableTextColor);
		TextBlock_Cost->SetColorAndOpacity(AvailableTextColor);
	}
	else
	{
		TextBlock_AbilityName->SetColorAndOpacity(UnavailableTextColor);
		TextBlock_CostType->SetColorAndOpacity(UnavailableTextColor);
		TextBlock_Cost->SetColorAndOpacity(UnavailableTextColor);
	}
	
	DescriptionText = FText::FromString(AbilityData->GetDescription());
}

void ULshPF_AbilityListEntry::NativePreConstruct()
{
	Super::NativePreConstruct();
	Background->SetBrush(DefaultBackgroundBrush);
}
