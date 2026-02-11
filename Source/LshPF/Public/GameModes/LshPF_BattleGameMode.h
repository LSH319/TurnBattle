// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LshPF_DataTableRow.h"
#include "GameModes/LshPF_GameModeBase.h"
#include "LshPF_BattleGameMode.generated.h"

class ULshPF_BattleComponent;
class ILshPF_BattleInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusUIReady);

USTRUCT(BlueprintType)
struct FTurnTableData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float RequireTP;
	
	ILshPF_BattleInterface* TargetCharacter;

	FTurnTableData() : RequireTP(0.f), TargetCharacter(nullptr) {}

	FTurnTableData(float _RequireTime, ILshPF_BattleInterface* TargetCharacter)
		: RequireTP(_RequireTime), TargetCharacter(TargetCharacter) {}
};
/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_BattleGameMode : public ALshPF_GameModeBase
{
	GENERATED_BODY()

public:
	//~ Begin ACharacter Interface
	virtual void PostInitializeComponents() override;;
	//~ End ACharacter Interface

	//캐릭터에서 begin play 시 호출될 함수
	void CharacterReady(ILshPF_BattleInterface* RequestBattleInterface);
	//Turn Table 에 삼입 요청을 위한 함수
	void RequestAddTurnTable(ILshPF_BattleInterface* RequestBattleInterface);
	//Turn 종료를 GM 에 알리기 위한 함수
	void TargetTurnEnd(ILshPF_BattleInterface* RequestBattleInterface);
	//Enemy 생성 시 DT 에서 Attribute 정보를 얻기 위한 함수
	FEnemyAttribute* GetEnemyAttributeByKeyName(FName EnemyKeyName) const;

	//Command 관련 Widget 준비여부 체크를 위한 함수, Status UI 와는 별도
	UFUNCTION(BlueprintCallable)
	void SetUIReady(bool NewIsUIReady);

	/*
	 * Status UI 준비 완료여부 확인을 위한 Delegate
	 * Status UI 가 UI Subsystem 에서 OnBattleComponentDelegate 에 대한 bind 완료 후 호출할것
	 */
	UPROPERTY(BlueprintCallable)
	FStatusUIReady StatusUIReady;
	
protected:
	void SortTurnTable();
	bool IsGameReady() const;
	
	UFUNCTION(BlueprintCallable)
	void GrantTurn();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TurnStartTP = 100.f;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* EnemyAttributeData;
	
	float GlobalTimer = 0.f;

	TArray<FTurnTableData> TurnTable;
	
	TArray<ILshPF_BattleInterface*> PlayerCharacterList;
	TArray<ILshPF_BattleInterface*> EnemyCharacterList;

private:
	TQueue<ULshPF_BattleComponent*> WaitingRegisterComponents;
	bool IsStatusUIReady = false;
	bool IsTurnGranted = false;
	bool IsUIReady = false;

	UFUNCTION()
	void StatusUIReadyCallBack();
};
