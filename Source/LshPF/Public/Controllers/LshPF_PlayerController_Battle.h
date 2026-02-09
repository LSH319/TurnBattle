// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "LshPF_PlayerController_Battle.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_PlayerController_Battle : public ALshPF_PlayerControllerBase
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input/Battle", meta = (AllowPrivateAccess = "true"))
	UInputAction* BattleAttackAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input/Battle", meta = (AllowPrivateAccess = "true"))
	UInputAction* BattleGuardAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input/Battle", meta = (AllowPrivateAccess = "true"))
	UInputAction* BattleOpenSkillListAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input/Battle", meta = (AllowPrivateAccess = "true"))
	UInputAction* BattleOpenItemListAction;
};
