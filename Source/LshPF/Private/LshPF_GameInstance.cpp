// Fill out your copyright notice in the Description page of Project Settings.


#include "LshPF_GameInstance.h"

int32 ULshPF_GameInstance::GetAllCharacterCount() const
{
	return PlayerCharacterInfo.Num() + EnemyCharacterCount;
}

TMap<FName, TArray<FName>> ULshPF_GameInstance::GetPlayerCharacterInfo()
{
	//todo : 테스트용, 삭제 필요 삭제 후 const
	PlayerCharacterInfo.Add("001", {"001","101"});
	PlayerCharacterInfo.Add("002", {"002","102"});
	PlayerCharacterInfo.Add("003", {"201","202"});
	PlayerCharacterInfo.Add("004", {"001","002","101","102","201","202"});
	
	return PlayerCharacterInfo;
}

int32 ULshPF_GameInstance::GetEnemyCharacterCount() const
{
	return EnemyCharacterCount;
}


void ULshPF_GameInstance::SetEnemyCharacterCount(int32 NewEnemyCharacterCount)
{
	EnemyCharacterCount = NewEnemyCharacterCount;
}

void ULshPF_GameInstance::SetItemInItemBox(FName ItemKey, int32 ItemCount)
{
	ItemBoxInfo.Add(ItemKey, ItemCount);
}

TMap<FName, int32> ULshPF_GameInstance::GetItemBoxInfo()
{
	//todo : 테스트용, 삭제 필요 삭제 후 const
	ItemBoxInfo.Add("Item_001", 3);
	ItemBoxInfo.Add("Item_002", 3);
	return ItemBoxInfo;
}

void ULshPF_GameInstance::SetPlayerCharacterInfo(TMap<FName, TArray<FName>> InPlayerCharacterInfo)
{
	PlayerCharacterInfo = InPlayerCharacterInfo;
}
