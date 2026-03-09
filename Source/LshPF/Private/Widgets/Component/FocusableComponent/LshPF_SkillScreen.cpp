// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Component/FocusableComponent/LshPF_SkillScreen.h"

#include "LshPF_FunctionLibrary.h"
#include "LshPF_GameplayTags.h"
#include "Ability/LshPF_Ability.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Controllers/LshPF_PlayerController_Battle.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/LshPF_ListView.h"
#include "Widgets/Component/FocusableComponent/LshPF_SelectTarget.h"

void ULshPF_SkillScreen::WidgetConfirmAction()
{
	Super::WidgetConfirmAction();
	ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld());

	if (ULshPF_Ability* SelectedAbility = AbilityList->GetSelectedItem<ULshPF_Ability>())
	{
		if (SelectedAbility->IsCanActivate())
		{
			UISubsystem->PushSoftWidgetToStackAsync(
				LshPF_GameplayTags::LshPF_WidgetStack_GameHud,
				ULshPF_FunctionLibrary::GetSoftFocusableWidgetBaseClassByTag(LshPF_GameplayTags::LshPF_Widget_TargetSelect),
				[this, SelectedAbility](ULshPF_FocusableWidgetBase* PushedWidget)
				{
					if (ULshPF_SelectTarget* SelectTargetWidget = Cast<ULshPF_SelectTarget>(PushedWidget))
					{
						SelectTargetWidget->SetSelectAbility(SelectedAbility);
					}
					if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				});
		}
	}
}

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

void ULshPF_SkillScreen::BeforeDestroyedEvent()
{
	Super::BeforeDestroyedEvent();
	ALshPF_PlayerController_Battle* CachedPlayerController= Cast<ALshPF_PlayerController_Battle>(GetOwningPlayer());
	CachedPlayerController->SetBattleSettingDefault(true);
	CachedPlayerController->RemoveOnTurnEndRemoveWidget(this);
}

void ULshPF_SkillScreen::DescriptionTextUpdate(FText DescriptionText)
{
	TextBlock_AbilityDescription->SetText(DescriptionText);
}
