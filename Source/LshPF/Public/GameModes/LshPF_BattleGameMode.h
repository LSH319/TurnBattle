// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LshPF_DataTableRow.h"
#include "GameModes/LshPF_GameModeBase.h"
#include "LshPF_BattleGameMode.generated.h"

class ILshPF_BattleInterface;

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
	void RequestAddTurnTable(ILshPF_BattleInterface* RequestBattleComponent);
	void TargetTurnEnd(ILshPF_BattleInterface* RequestBattleComponent);
	FEnemyAttribute* GetEnemyAttributeByKeyName(FName EnemyKeyName);
	
protected:
	void SortTurnTable();
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
	bool IsTurnGranted = false;
};
