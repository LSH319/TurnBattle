// Fill out your copyright notice in the Description page of Project Settings.


#include "LshPF_GameInstance.h"

int32 ULshPF_GameInstance::GetAllCharacterCount() const
{
	return PlayerCharacterCount + EnemyCharacterCount;
}

int32 ULshPF_GameInstance::GetPlayerCharacterCount() const
{
	return PlayerCharacterCount;
}

int32 ULshPF_GameInstance::GetEnemyCharacterCount() const
{
	return EnemyCharacterCount;
}

void ULshPF_GameInstance::SetPlayerCharacterCount(int32 NewPlayerCharacterCount)
{
	PlayerCharacterCount = NewPlayerCharacterCount;
}

void ULshPF_GameInstance::SetEnemyCharacterCount(int32 NewEnemyCharacterCount)
{
	EnemyCharacterCount = NewEnemyCharacterCount;
}
