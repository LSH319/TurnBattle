// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerCharacterInfo.generated.h"

class ALshPF_PlayerBattleCharacter;

USTRUCT(BlueprintType)
struct FPlayerBattleCharacterInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<ALshPF_PlayerBattleCharacter> PlayerCharacterClass;
	
	UPROPERTY(EditDefaultsOnly)
	int16 CharacterOrderPriority = 0;
};

/**
 * 
 */
UCLASS()
class LSHPF_API UPlayerCharacterInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	TSoftClassPtr<ALshPF_PlayerBattleCharacter> GetPlayerCharacterClassByKeyName(FName EnemyKeyName);
	int16 GetCharacterOrderPriorityByKeyName(FName EnemyKeyName);
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FPlayerBattleCharacterInfo> PlayerCharacterClassInfoMap;
	//TMap<FName, TSoftClassPtr<ALshPF_PlayerBattleCharacter>> PlayerCharacterClassInfoMap;
};
