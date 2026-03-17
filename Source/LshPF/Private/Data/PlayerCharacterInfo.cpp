// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/PlayerCharacterInfo.h"

TSoftClassPtr<ALshPF_PlayerBattleCharacter> UPlayerCharacterInfo::GetPlayerCharacterClassByKeyName(FName EnemyKeyName)
{
	return PlayerCharacterClassInfoMap.FindChecked(EnemyKeyName).PlayerCharacterClass;
}

int16 UPlayerCharacterInfo::GetCharacterOrderPriorityByKeyName(FName EnemyKeyName)
{
	return PlayerCharacterClassInfoMap.FindChecked(EnemyKeyName).CharacterOrderPriority;
}

FText UPlayerCharacterInfo::GetCharacterNameByKeyName(FName EnemyKeyName)
{
	return PlayerCharacterClassInfoMap.FindChecked(EnemyKeyName).CharacterName;
}
