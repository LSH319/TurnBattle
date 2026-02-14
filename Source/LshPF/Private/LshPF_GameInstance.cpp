// Fill out your copyright notice in the Description page of Project Settings.


#include "LshPF_GameInstance.h"

int32 ULshPF_GameInstance::GetAllCharacterCount() const
{
	return PlayerCharacterKeyNames.Num() + EnemyCharacterCount;
}

TArray<FName> ULshPF_GameInstance::GetPlayerCharacterKeyNames() const
{
	return PlayerCharacterKeyNames;
}

int32 ULshPF_GameInstance::GetEnemyCharacterCount() const
{
	return EnemyCharacterCount;
}


void ULshPF_GameInstance::SetEnemyCharacterCount(int32 NewEnemyCharacterCount)
{
	EnemyCharacterCount = NewEnemyCharacterCount;
}
