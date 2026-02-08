// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LshPF_BattleGameMode.h"

#include "Interface/LshPF_BattleInterface.h"

void ALshPF_BattleGameMode::RequestAddTurnTable(ILshPF_BattleInterface* RequestBattleComponent)
{
	int32 CharacterSpeed = RequestBattleComponent->GetAttribute(EAttributeType::CurrentSpeed);
	float RequireTime = GlobalTimer + (TurnStartTP / CharacterSpeed);
	FTurnTableData TurnTableData(RequireTime, RequestBattleComponent);

	TurnTable.Add(TurnTableData);

	if (RequestBattleComponent->IsPlayerCharacter())
	{
		PlayerCharacterList.Add(RequestBattleComponent);
	}
	else
	{
		EnemyCharacterList.Add(RequestBattleComponent);
	}
	
	SortTurnTable();
}

void ALshPF_BattleGameMode::TargetTurnEnd(ILshPF_BattleInterface* RequestBattleComponent)
{
	RequestAddTurnTable(RequestBattleComponent);
	GrantTurn();
}

FEnemyAttribute* ALshPF_BattleGameMode::GetEnemyAttributeByKeyName(FName EnemyKeyName)
{
	return EnemyAttributeData->FindRow<FEnemyAttribute>(EnemyKeyName, FString("EnemyKeyName Is Error"));
}

void ALshPF_BattleGameMode::SortTurnTable()
{
	TurnTable.Sort([](
		const FTurnTableData& A, const FTurnTableData& B)
		{
			return A.RequireTP < B.RequireTP;
		});
}

void ALshPF_BattleGameMode::GrantTurn()
{
	TurnTable[0].TargetCharacter->TurnStart();
	GlobalTimer = TurnTable[0].RequireTP;
	
	TurnTable.RemoveAt(0);
}