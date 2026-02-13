// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerController_Battle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LshPF_FunctionLibrary.h"
#include "LshPF_GameplayTags.h"
#include "Data/InputActionGameplayTagInfo.h"
#include "GameModes/LshPF_BattleGameMode.h"
#include "Interface/LshPF_BattleInterface.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"

void ALshPF_PlayerController_Battle::ExecuteInputActionByGameplayTag(const FGameplayTag TargetGameplayTag)
{
	//Input 에 대한 Action 실행 여부 체크
	if (IsEnableInput)
	{
		IsEnableInput = false;
		//들어온 Tag 에 따라 필요한 로직을 작성한 함수 실행
        if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_Attack))
        {
        	UE_LOG(LogTemp, Warning, TEXT("Attack"));
        	CachedBattleGameMode->GetRecentOwingTurnCharacter()->TurnEnd();
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_Guard))
        {
        	UE_LOG(LogTemp, Warning, TEXT("Guard"));
        	CachedBattleGameMode->GetRecentOwingTurnCharacter()->TurnEnd();
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_OpenSkill))
        {
        	UE_LOG(LogTemp, Warning, TEXT("OpenSkill"));

        	AddWidgetToScreenByTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, LshPF_GameplayTags::LshPF_Widget_Skill);
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_OpenItem))
        {
        	UE_LOG(LogTemp, Warning, TEXT("OpenItem"));

        	AddWidgetToScreenByTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, LshPF_GameplayTags::LshPF_Widget_Item);
        }
	}
}

UInputAction* ALshPF_PlayerController_Battle::GetInputActionByGameplayTag(FGameplayTag TargetGameplayTag)
{
	return InputActionGameplayTagInfo->GetInputActionByGameplayTag(TargetGameplayTag);
}

void ALshPF_PlayerController_Battle::SetIsEnableInput(bool InIsEnableInput)
{
	IsEnableInput = InIsEnableInput;
}

void ALshPF_PlayerController_Battle::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	for (const TTuple<FGameplayTag, UInputAction*> Info : InputActionGameplayTagInfo->InputActionGameplayTagMap)
	{
		//InputActionGameplayTagInfo 의 Map 을 순회하면서 바인딩 실행
		//FGameplayTag 를 매갭변수로 넘겨줘 동작 구분 시 사용
		EnhancedInputComponent->BindAction(Info.Value, ETriggerEvent::Started, this, &ThisClass::ExecuteInputActionByGameplayTag, Info.Key);
	}
}

ALshPF_BattleGameMode* ALshPF_PlayerController_Battle::GetBattleGameMode()
{
	if (!CachedBattleGameMode)
	{
		CachedBattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	}
	return CachedBattleGameMode;
}

void ALshPF_PlayerController_Battle::AddWidgetToScreenByTag(FGameplayTag WidgetStackTag, FGameplayTag WidgetTag,
	bool IsWidgetGetFocus)
{
	ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld());

	UISubsystem->PushSoftWidgetToStackAsync(
		WidgetStackTag,
		ULshPF_FunctionLibrary::GetSoftFocusableWidgetBaseClassByTag(WidgetTag),
		[this, IsWidgetGetFocus](ULshPF_FocusableWidgetBase* PushedWidget)
		{
			PushedWidget->SetOwningPlayer(this);
			if (IsWidgetGetFocus)
			{
				if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
	            {
            		WidgetToFocus->SetFocus();
	            }
			}
			IsEnableInput = true;
		});
}
