// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "LshPF_PlayerController_Battle.generated.h"

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
	UFUNCTION(BlueprintCallable)
	void ExecuteInputActionByGameplayTag(FGameplayTag TargetGameplayTag);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UInputAction* GetInputActionByGameplayTag(FGameplayTag TargetGameplayTag);

	void SetIsEnableInput(bool InIsEnableInput);
	
protected:
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintPure)
	ALshPF_BattleGameMode* GetBattleGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input/Data")
	UInputActionGameplayTagInfo* InputActionGameplayTagInfo;

	bool IsEnableInput = false;
	
private:
	UPROPERTY()
	ALshPF_BattleGameMode* CachedBattleGameMode;
};
