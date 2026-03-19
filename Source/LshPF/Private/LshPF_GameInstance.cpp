// Fill out your copyright notice in the Description page of Project Settings.


#include "LshPF_GameInstance.h"

int32 ULshPF_GameInstance::GetAllCharacterCount() const
{
	return PlayerCharacterInfo.Num() + EnemyCharacterCount;
}

int32 ULshPF_GameInstance::BP_GetEnemyCharacterCount() const
{
	return GetEnemyCharacterCount();
}

TMap<FName, int32> ULshPF_GameInstance::BP_GetItemBoxInfo() const
{
	return GetItemBoxInfo();
}

void ULshPF_GameInstance::BP_SetEnemyCharacterCount(int32 NewEnemyCharacterCount)
{
	SetEnemyCharacterCount(NewEnemyCharacterCount);
}

void ULshPF_GameInstance::BP_SetItemInItemBox(FName ItemKey, int32 ItemCount)
{
	SetItemInItemBox(ItemKey, ItemCount);
}

TMap<FName, TArray<FName>> ULshPF_GameInstance::GetPlayerCharacterInfo() const
{
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

TMap<FName, int32> ULshPF_GameInstance::GetItemBoxInfo() const
{
	return ItemBoxInfo;
}

void ULshPF_GameInstance::SetPlayerCharacterInfo(TMap<FName, TArray<FName>> InPlayerCharacterInfo)
{
	PlayerCharacterInfo = InPlayerCharacterInfo;
}
