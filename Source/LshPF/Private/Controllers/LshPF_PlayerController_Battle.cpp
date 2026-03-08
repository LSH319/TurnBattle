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
#include "Kismet/GameplayStatics.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "Widgets/Component/FocusableComponent/LshPF_SkillScreen.h"

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
        	ToggleTargetingAllTargets(false);
        	AddSkillScreenToScreen();
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_OpenItem))
        {
        	AddWidgetToScreenByTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, LshPF_GameplayTags::LshPF_Widget_Item);
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_SelectTarget_Prev))
        {
	        switch (TargetType) {
	        case ETargetType::EnemySingle:
	        	Command_ChangeTarget_Enemy(true);
		        break;
	        case ETargetType::PlayerSingle:
	        	Command_ChangeTarget_Player(false);
		        break;
	        case ETargetType::EnemyAll:
	        case ETargetType::PlayerAll:
	        case ETargetType::Unknown:
		        break;
	        }
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_SelectTarget_Next))
        {
        	switch (TargetType) {
        	case ETargetType::EnemySingle:
        		Command_ChangeTarget_Enemy(false);
        		break;
        	case ETargetType::PlayerSingle:
        		Command_ChangeTarget_Player(true);
        		break;
        	case ETargetType::EnemyAll:
			case ETargetType::PlayerAll:
        	case ETargetType::Unknown:
        		break;
        	}
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_CharacterInfo))
        {
        	AddWidgetToScreenByTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, LshPF_GameplayTags::LshPF_Widget_CharacterInfo);
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_TargetTypeSwitch))
        {
        	ToggleTargetingAllTargets(false);
        	
	        switch (TargetType) {
	        case ETargetType::EnemySingle:
	        case ETargetType::EnemyAll:
	        	TargetType = ETargetType::PlayerSingle;
	        	CachedTargetByIndex(TargetingPlayerNum, false);
		        break;
	        case ETargetType::PlayerSingle:
	        case ETargetType::PlayerAll:
	        	TargetType = ETargetType::EnemySingle;
	        	CachedTargetByIndex(TargetingEnemyNum, true);
		        break;
	        case ETargetType::Unknown:
		        break;
	        }
        	
        	ToggleTargetingAllTargets(true);
        	OnTargetChange.Broadcast(TargetList[0]->GetBattleComponent());
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_DefaultConfirm))
        {
        	DefaultConfirmAction_Callback();
        }
        else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_DefaultBack))
        {
        	DefaultBackAction_Callback();
        }
	}
}

void ALshPF_PlayerController_Battle::SetIsEnableInput(bool InIsEnableInput)
{
	IsEnableInput = InIsEnableInput;
}

void ALshPF_PlayerController_Battle::SetBattleSettingDefault(bool IsTargetToggleActive)
{
	ToggleTargetingAllTargets(false);
	
	TargetType = ETargetType::EnemySingle;
	CachedTargetByIndex(TargetingEnemyNum, true);
	SetCharacterRotationToTarget();
	ResetViewTarget();
	if (IsTargetToggleActive)
	{
		ToggleTargetingAllTargets(true);
	}
}

void ALshPF_PlayerController_Battle::SetTargetTypeWithSetViewTarget(ETargetType InETargetType)
{
	TargetType = InETargetType;
	
	switch (TargetType)
	{
	case ETargetType::EnemySingle:
	    GetBattleGameMode()->GetEnemyCharacterByIndex(TargetingEnemyNum)->SetViewTargetSelf(true);
	    break;
	case ETargetType::PlayerSingle:
	    GetBattleGameMode()->GetPlayerCharacterByIndex(TargetingPlayerNum)->SetViewTargetSelf(true);
	    break;
	case ETargetType::EnemyAll:
	case ETargetType::PlayerAll:
	    if (AllTargetViewTarget)
	    {
     		SetViewTarget(AllTargetViewTarget);
	    }
	    break;
	case ETargetType::Unknown:
	default:
	    break;
	}
	
	SetToggleByTargetType(InETargetType);
}

void ALshPF_PlayerController_Battle::PlayerCharacterTurnStartEvent()
{
	SetBattleSettingDefault(true);
}

TArray<ILshPF_BattleInterface*> ALshPF_PlayerController_Battle::GetTargetList()
{
	return TargetList;
}

ULshPF_BattleComponent* ALshPF_PlayerController_Battle::GetTargetBattleComponent()
{
	return TargetList[0]->GetBattleComponent();
}

void ALshPF_PlayerController_Battle::ResetViewTarget()
{
	if (GetBattleGameMode()->GetRecentOwingTurnCharacter()->IsPlayerCharacter())
	{
		GetBattleGameMode()->GetRecentOwingTurnCharacter()->SetViewTargetSelf(false);
	}
	else
	{
		GetBattleGameMode()->GetRecentOwingTurnCharacter()->SetViewTargetSelf(true);
	}
}

void ALshPF_PlayerController_Battle::SetTargetType(ETargetType InETargetType)
{
	TargetType = InETargetType;
}

void ALshPF_PlayerController_Battle::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("AllTarget"), FoundActors);
	AllTargetViewTarget = FoundActors[0];
}

void ALshPF_PlayerController_Battle::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	for (const TTuple<FGameplayTag, UInputAction*> Info : InputActionGameplayTagInfo->InputActionGameplayTagMap)
	{
		//중복 바인딩 방지
		if (Info.Key.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_DefaultBack) || Info.Key.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_DefaultConfirm)) continue;
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

void ALshPF_PlayerController_Battle::AddSkillScreenToScreen()
{
	IsEnableInput = false;
	ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld());

	UISubsystem->PushSoftWidgetToStackAsync(
		LshPF_GameplayTags::LshPF_WidgetStack_GameHud,
		ULshPF_FunctionLibrary::GetSoftFocusableWidgetBaseClassByTag(LshPF_GameplayTags::LshPF_Widget_Skill),
		[this](ULshPF_FocusableWidgetBase* PushedWidget)
		{
			ULshPF_SkillScreen* SkillScreen = CastChecked<ULshPF_SkillScreen>(PushedWidget);
			SkillScreen->InitAbilityList(GetBattleGameMode()->GetRecentOwingTurnCharacter()->GetBattleComponent()->GetAbilityList());
			SkillScreen->SetOwningPlayer(this);
			if (UWidget* WidgetToFocus = SkillScreen->GetDesiredFocusTarget())
			{
				WidgetToFocus->SetFocus();
			}
			IsEnableInput = true;
		});
}

void ALshPF_PlayerController_Battle::ToggleTargetingAllTargets(bool IsActive)
{
	for (ILshPF_BattleInterface* Target : TargetList)
	{
		if (Target)
		{
			Target->ToggleTargeting(IsActive);
		}
	}
}

void ALshPF_PlayerController_Battle::SetToggleByTargetType(ETargetType InETargetType)
{
	ToggleTargetingAllTargets(false);
	TargetList.Empty();
	switch (TargetType)
	{
	case ETargetType::EnemySingle:
		CachedTargetByIndex(TargetingEnemyNum, true);
		break;
	case ETargetType::PlayerSingle:
		CachedTargetByIndex(TargetingPlayerNum, false);
		break;
	case ETargetType::EnemyAll:
		TargetList = GetBattleGameMode()->GetEnemyCharacters();
		break;
	case ETargetType::PlayerAll:
		TargetList = GetBattleGameMode()->GetPlayerCharacters();
		break;
	case ETargetType::Unknown:
	default:
		break;
	}
	ToggleTargetingAllTargets(true);
}

void ALshPF_PlayerController_Battle::CachedTargetByIndex(int32& TargetIndex, bool IsTargetEnemy)
{
	TargetList.Empty();
	ILshPF_BattleInterface* NewTarget;
	if (IsTargetEnemy)
	{
		NewTarget = GetBattleGameMode()->GetEnemyCharacterByIndex(TargetIndex);
	}
	else
	{
		NewTarget = GetBattleGameMode()->GetPlayerCharacterByIndex(TargetIndex);
	}
	TargetList.Add(NewTarget);
}

void ALshPF_PlayerController_Battle::SetCharacterRotationToTarget()
{
	//TurnCharacter Rotation 설정
	ILshPF_BattleInterface* TurnCharacter = GetBattleGameMode()->GetRecentOwingTurnCharacter();
	ILshPF_BattleInterface* TargetCharacter = GetBattleGameMode()->GetEnemyCharacterByIndex(TargetingEnemyNum);
	if (TurnCharacter && TargetCharacter)
	{
		TurnCharacter->SetLookAtRotation(TargetCharacter->GetBattleCharacterLocation());
	}
}


void ALshPF_PlayerController_Battle::PlayerCharacterTurnEndEvent()
{
	//Player 턴 종료를 위해 함수, 필요한 이벤트 처리
	ToggleTargetingAllTargets(false);
	TargetList.Empty();
}

void ALshPF_PlayerController_Battle::Command_Attack()
{
	if (ILshPF_BattleInterface* TurnCharacter = GetBattleGameMode()->GetRecentOwingTurnCharacter())
	{
		if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
		{
			UISubsystem->SetWidgetSwitcherVisibilityWithTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, ESlateVisibility::Hidden);
		}
		
		IsEnableInput = false;
		TurnCharacter->PlayAnimMontageByTag(LshPF_GameplayTags::LshPF_AnimMontage_Attack);
	}
}

void ALshPF_PlayerController_Battle::Command_Guard()
{
	if (ILshPF_BattleInterface* TurnCharacter = GetBattleGameMode()->GetRecentOwingTurnCharacter())
	{
		if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
		{
			UISubsystem->SetWidgetSwitcherVisibilityWithTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, ESlateVisibility::Hidden);
		}
		
		IsEnableInput = false;
		TurnCharacter->ToggleGuard(true);
	}
}

void ALshPF_PlayerController_Battle::Command_ChangeTarget_Enemy(bool IsPrev)
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
	
	CachedTargetByIndex(TargetingEnemyNum, true);
	//타켓 파티클 On
	ToggleTargetingAllTargets(true);

	SetCharacterRotationToTarget();
	OnTargetChange.Broadcast(TargetList[0]->GetBattleComponent());
}

void ALshPF_PlayerController_Battle::Command_ChangeTarget_Player(bool IsPrev)
{
	//타켓 파티클 Off
	ToggleTargetingAllTargets(false);
	
	if (IsPrev)
	{
		TargetingPlayerNum--;
	}
	else
	{
		TargetingPlayerNum++;
	}
	
	CachedTargetByIndex(TargetingPlayerNum, false);
	//타켓 파티클 On
	ToggleTargetingAllTargets(true);

	OnTargetChange.Broadcast(TargetList[0]->GetBattleComponent());
}
