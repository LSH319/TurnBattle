// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"
#include "LshPF_EnemyBattleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_EnemyBattleCharacter : public ALshPF_BattleCharacter_Base
{
	GENERATED_BODY()

public:
	//~ Begin ACharacter Interface
	virtual void PostInitializeComponents() override;
	//~ End ACharacter Interface

	//~ Begin LshPF_BattleInterface Interface
	virtual void TurnStart() override;
	//~ End LshPF_BattleInterface Interface
};
