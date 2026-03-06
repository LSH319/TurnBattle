// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_SkillScreen.h"

#include "Ability/LshPF_Ability.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/LshPF_ListView.h"

void ULshPF_SkillScreen::InitAbilityList(TArray<ULshPF_Ability*> CharacterAbilityList)
{
	for (ULshPF_Ability* Ability : CharacterAbilityList)
	{
		AbilityList->AddItem(Ability);
	}
	AbilityList->SetSelectedIndex(0);

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->OnButtonDescriptionTextUpdated.AddDynamic(this, &ThisClass::DescriptionTextUpdate);
	}
}

UListView* ULshPF_SkillScreen::GetSkillScreenListView()
{
	return AbilityList;
}

void ULshPF_SkillScreen::DescriptionTextUpdate(FText DescriptionText)
{
	TextBlock_AbilityDescription->SetText(DescriptionText);
}
