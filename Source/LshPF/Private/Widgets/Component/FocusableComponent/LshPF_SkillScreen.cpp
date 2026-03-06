// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_SkillScreen.h"

#include "Ability/LshPF_Ability.h"
#include "Components/ListView.h"

void ULshPF_SkillScreen::InitAbilityList(TArray<ULshPF_Ability*> CharacterAbilityList)
{
	for (ULshPF_Ability* Ability : CharacterAbilityList)
	{
		AbilityList->AddItem(Ability);
	}
	AbilityList->SetSelectedIndex(0);
}

UListView* ULshPF_SkillScreen::GetSkillScreenListView()
{
	return AbilityList;
}
