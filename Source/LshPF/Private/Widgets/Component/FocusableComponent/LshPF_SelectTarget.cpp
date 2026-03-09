// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_SelectTarget.h"

#include "Ability/LshPF_Ability.h"
#include "Controllers/LshPF_PlayerController_Battle.h"

void ULshPF_SelectTarget::WidgetConfirmAction()
{
	Super::WidgetConfirmAction();

	if (CachedAbility.IsValid())
	{
		CachedAbility->CommitAbility();
	}
}

void ULshPF_SelectTarget::WidgetBackAction()
{
	Super::WidgetBackAction();
	
	ALshPF_PlayerController_Battle* CachedPlayerController= Cast<ALshPF_PlayerController_Battle>(GetOwningPlayer());
	CachedPlayerController->SetBattleSettingDefault(false);
	
	RemoveFromParentStack();
}

void ULshPF_SelectTarget::SetSelectAbility(ULshPF_Ability* SelectedAbility)
{
	CachedAbility = SelectedAbility;

	ALshPF_PlayerController_Battle* CachedPlayerController= Cast<ALshPF_PlayerController_Battle>(GetOwningPlayer());
	CachedPlayerController->SetTargetTypeWithSetViewTarget(CachedAbility->GetTargetType());
	CachedPlayerController->SetTargetModifier(CachedAbility->GetAbilityModifier());
	CachedPlayerController->AddOnTurnEndRemoveWidget(this);
}

void ULshPF_SelectTarget::BeforeDestroyedEvent()
{
	Super::BeforeDestroyedEvent();
	
	ALshPF_PlayerController_Battle* CachedPlayerController= Cast<ALshPF_PlayerController_Battle>(GetOwningPlayer());
	CachedPlayerController->RemoveOnTurnEndRemoveWidget(this);
}
