// Fill out your copyright notice in the Description page of Project Settings.


#include "LshPF_GameInstance.h"

int32 ULshPF_GameInstance::GetAllCharacterCount() const
{
	return PlayerCharacterCount + EnemyCharacterCount;
}

void ULshPF_GameInstance::SetPlayerCharacterCount(int32 NewPlayerCharacterCount)
{
	PlayerCharacterCount = NewPlayerCharacterCount;
}

void ULshPF_GameInstance::SetEnemyCharacterCount(int32 NewEnemyCharacterCount)
{
	EnemyCharacterCount = NewEnemyCharacterCount;
}
