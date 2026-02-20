// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "LshPF_PlayerController_Battle.generated.h"

class ILshPF_BattleInterface;
class UInputActionGameplayTagInfo;
class ALshPF_BattleGameMode;
/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_PlayerController_Battle : public ALshPF_PlayerControllerBase
{
	GENERATED_BODY()

public:
	/*
	 * Button 의 Onclick 에 Bind 될 함수
	 * Tag 에 따라 지정된 로직을 실행
	 * Button 의 Onclick 과 IA 의 동작을 통일하기위해 사용
	 */
	virtual void ExecuteInputActionByGameplayTag(FGameplayTag TargetGameplayTag) override;
	
	void SetIsEnableInput(bool InIsEnableInput);
	/*
	 * Player Turn 시작 시 Character 에서 호출하여 이벤트 처리를 위한 함수
	 */
	void PlayerCharacterTurnStartEvent();
	
protected:
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintPure)
	ALshPF_BattleGameMode* GetBattleGameMode();

	bool IsEnableInput = false;
	
private:
	UPROPERTY()
	ALshPF_BattleGameMode* CachedBattleGameMode;

	int32 TargetingEnemyNum = 0;
	TArray<ILshPF_BattleInterface*> TargetList;
	
	/*
	 * FInputActionValue 의 값을 사용하기 위해 IA 에 바인딩 될 함수
	 * ExecuteInputActionByGameplayTag 를 호출하여 Button 과 동작을 통일
	 */
	void ExecuteInputAction(const FInputActionValue& Value, const FGameplayTag TargetGameplayTag);
	
	/*
	 * WidgetStackTag LshPF.WidgetStack 형식의 Tag, Widget 이 추가될 Stack
	 * WidgetTag LshPF.Widget 형식의 Tag, 추가할 Widget 을 표시하는 Tag
	 * IsWidgetGetFocus 추가 된 Widget 이 Focus 를 가질지 여부, Default true
	 */
	void AddWidgetToScreenByTag(FGameplayTag WidgetStackTag, FGameplayTag WidgetTag, bool IsWidgetGetFocus = true);

	/*
	 * TargetList 에 포함된 요소들의 Targeting Toggle을 위한 함수
	 */
	void ToggleTargetingAllTargets(bool IsActive);
	
	/*
	 * Index 를 통해 Target Enemy 를 TargetList에 추가
	 * 파라미터를 & 로 받아 값이 배열의 범위를 넘어가도 조정
	 */
	void CachedTargetEnemyByIndex(int32& TargetIndex);
	void SetCharacterRotationToTarget();
	void CallTurnEnd();
	
	void Command_Attack();
	void Command_Guard();
	void Command_ChangeTarget(bool IsPrev);
};