// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "EnemyMeshInfo.generated.h"

class ALshPF_EnemyBattleCharacter;

USTRUCT(BlueprintType)
struct FEnemyMeshData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FText CharacterName;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAnimInstance> AnimClass;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> EnemyMontageMap;	
};

/**
 * 
 */
UCLASS()
class LSHPF_API UEnemyMeshInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FEnemyMeshData GetEnemyMeshInfoByKeyName(FName EnemyKeyName);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALshPF_EnemyBattleCharacter> EnemyBattleCharacterBaseClass;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FEnemyMeshData> EnemyMeshInfoMap;
};
