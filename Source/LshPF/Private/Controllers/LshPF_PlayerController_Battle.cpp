// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerController_Battle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LshPF_FunctionLibrary.h"
#include "LshPF_GameplayTags.h"
#include "Component/LshPF_BattleComponent.h"
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
		//들어온 Tag 에 따라 필요한 로직을 작성한 함수 실행
        if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_Attack))
        {
        	Command_Attack();
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_Guard))
        {
        	Command_Guard();
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_OpenSkill))
        {
        	AddWidgetToScreenByTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, LshPF_GameplayTags::LshPF_Widget_Skill);
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_OpenItem))
        {
        	AddWidgetToScreenByTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, LshPF_GameplayTags::LshPF_Widget_Item);
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_SelectTarget_Prev))
        {
        	Command_ChangeTarget(true);
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_SelectTarget_Next))
        {
        	Command_ChangeTarget(false);
        }
	}
}

void ALshPF_PlayerController_Battle::SetIsEnableInput(bool InIsEnableInput)
{
	IsEnableInput = InIsEnableInput;
}

void ALshPF_PlayerController_Battle::PlayerCharacterTurnStartEvent()
{
	CachedTargetEnemyByIndex(TargetingEnemyNum);
	ToggleTargetingAllTargets(true);
}

void ALshPF_PlayerController_Battle::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	for (const TTuple<FGameplayTag, UInputAction*> Info : InputActionGameplayTagInfo->InputActionGameplayTagMap)
	{
		//InputActionGameplayTagInfo 의 Map 을 순회하면서 바인딩 실행
		//FGameplayTag 를 매갭변수로 넘겨줘 동작 구분 시 사용
		EnhancedInputComponent->BindAction(Info.Value, ETriggerEvent::Started, this, &ThisClass::ExecuteInputAction, Info.Key);
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

void ALshPF_PlayerController_Battle::ExecuteInputAction(const FInputActionValue& Value,
	const FGameplayTag TargetGameplayTag)
{
	ExecuteInputActionByGameplayTag(TargetGameplayTag);
}

void ALshPF_PlayerController_Battle::AddWidgetToScreenByTag(FGameplayTag WidgetStackTag, FGameplayTag WidgetTag,
                                                            bool IsWidgetGetFocus)
{
	IsEnableInput = false;
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

void ALshPF_PlayerController_Battle::ToggleTargetingAllTargets(bool IsActive)
{
	for (ILshPF_BattleInterface* Target : TargetList)
	{
		Target->ToggleTargeting(IsActive);
	}
}

void ALshPF_PlayerController_Battle::CachedTargetEnemyByIndex(int32& TargetIndex)
{
	TargetList.Empty();
	ILshPF_BattleInterface* NewTarget = GetBattleGameMode()->GetEnemyCharacterByIndex(TargetIndex);
	TargetList.Add(NewTarget);
}

void ALshPF_PlayerController_Battle::CallTurnEnd()
{
	//Player 턴 종료를 위해 함수, 필요한 이벤트 처리
	ToggleTargetingAllTargets(false);
	TargetList.Empty();
	GetBattleGameMode()->GetRecentOwingTurnCharacter()->TurnEnd();
}

void ALshPF_PlayerController_Battle::Command_Attack()
{
	IsEnableInput = false;
	ILshPF_BattleInterface* TurnCharacter = GetBattleGameMode()->GetRecentOwingTurnCharacter();
	ILshPF_BattleInterface* TargetCharacter = GetBattleGameMode()->GetEnemyCharacterByIndex(TargetingEnemyNum);
	
	if (TurnCharacter && TargetCharacter)
	{
		FBattleAttributeModifier BattleAttributeModifier = TurnCharacter->GetBattleComponent()->CreateBattleAttributeModifier(EAttributeType::CurrentHealth, EAttributeType::CurrentAttack, 1.f);
		TurnCharacter->PlayAnimMontageByTag(LshPF_GameplayTags::LshPF_AnimMontage_Attack);
		TurnCharacter->GetBattleComponent()->ApplyDamageToTarget(
			TargetCharacter->GetBattleComponent(),
			TurnCharacter->GetBattleComponent(),
			BattleAttributeModifier);
	}
	
	CallTurnEnd();
}

void ALshPF_PlayerController_Battle::Command_Guard()
{
	IsEnableInput = false;
	
	ILshPF_BattleInterface* TurnCharacter = GetBattleGameMode()->GetRecentOwingTurnCharacter();
	
	if (TurnCharacter)
	{
		TurnCharacter->ToggleGuard(true);
	}
	
	CallTurnEnd();
}

void ALshPF_PlayerController_Battle::Command_ChangeTarget(bool IsPrev)
{
	//타켓 파티클 Off
	ToggleTargetingAllTargets(false);
	
	if (IsPrev)
	{
		TargetingEnemyNum--;
	}
	else
	{
		TargetingEnemyNum++;
	}
	
	CachedTargetEnemyByIndex(TargetingEnemyNum);
	//타켓 파티클 On
	ToggleTargetingAllTargets(true);
}