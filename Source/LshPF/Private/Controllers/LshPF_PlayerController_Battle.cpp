// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LshPF_PlayerController_Battle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LshPF_GameplayTags.h"
#include "Data/InputActionGameplayTagInfo.h"
#include "GameModes/LshPF_BattleGameMode.h"

void ALshPF_PlayerController_Battle::ExecuteInputActionByGameplayTag(const FGameplayTag TargetGameplayTag)
{
	//들어온 Tag 에 따라 필요한 로직을 작성한 함수 실행
	if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_Attack))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
	}
	else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_Guard))
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard"));
	}
	else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_OpenSkill))
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenSkill"));
	}
	else if (TargetGameplayTag.MatchesTagExact(LshPF_GameplayTags::LshPF_InputAction_OpenItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenItem"));
	}
}

UInputAction* ALshPF_PlayerController_Battle::GetInputActionByGameplayTag(FGameplayTag TargetGameplayTag)
{
	return InputActionGameplayTagInfo->GetInputActionByGameplayTag(TargetGameplayTag);
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
