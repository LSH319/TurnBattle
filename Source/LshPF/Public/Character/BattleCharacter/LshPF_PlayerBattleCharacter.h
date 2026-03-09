// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"
#include "LshPF_PlayerBattleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_PlayerBattleCharacter : public ALshPF_BattleCharacter_Base
{
	GENERATED_BODY()

public:
	ALshPF_PlayerBattleCharacter();
	
	//~ Begin ACharacter Interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~ End ACharacter Interface

	//~ Begin LshPF_BattleInterface Interface
	virtual void TurnStart() override;
	virtual void TurnEnd() override;
	virtual bool IsPlayerCharacter() override;
	//~ End LshPF_BattleInterface Interface
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharacterLevel = 0;
	
	UPROPERTY(EditDefaultsOnly)
	UCurveTable* CharacterAttributeData;
	
private:
	/*
	 * Base Attribute 값을 Curve Table 에서 받아오기
	 * 잘못된 값이 들어올 경우 -1 반환
	 * AttributeType 원하는 Base Attribute
	 * Level CurveTable 의 Time
	 * return AttributeType 과 Level 에 따른 CurveTable 값
	 */
	float GetBaseAttributeFromCurveTable(EAttributeType AttributeType, int32 Level = 0);
};
