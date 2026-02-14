// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerCharacterInfo.generated.h"

class ALshPF_PlayerBattleCharacter;
/**
 * 
 */
UCLASS()
class LSHPF_API UPlayerCharacterInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	TSoftClassPtr<ALshPF_PlayerBattleCharacter> GetPlayerCharacterClassByKeyName(FName EnemyKeyName);
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, TSoftClassPtr<ALshPF_PlayerBattleCharacter>> PlayerCharacterClassInfoMap;
};
