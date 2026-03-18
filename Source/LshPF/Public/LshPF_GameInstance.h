// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LshPF_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, DisplayName = "GetEnemyCharacterCount")
	int32 BP_GetEnemyCharacterCount() const;
	UFUNCTION(BlueprintPure, DisplayName = "GetItemBoxInfo")
	TMap<FName, int32> BP_GetItemBoxInfo() const;
	UFUNCTION(BlueprintCallable, DisplayName = "SetEnemyCharacterCount")
	void BP_SetEnemyCharacterCount(int32 NewEnemyCharacterCount);
	UFUNCTION(BlueprintCallable, DisplayName = "SetItemInItemBox")
	void BP_SetItemInItemBox(FName ItemKey, int32 ItemCount);
	
	int32 GetAllCharacterCount() const;
	TMap<FName, TArray<FName>> GetPlayerCharacterInfo();
	int32 GetEnemyCharacterCount() const;
	TMap<FName, int32> GetItemBoxInfo() const;

	void SetPlayerCharacterInfo(TMap<FName, TArray<FName>> InPlayerCharacterInfo);
	void SetEnemyCharacterCount(int32 NewEnemyCharacterCount);
	void SetItemInItemBox(FName ItemKey, int32 ItemCount);
	
private:
	//todo : test 를 위해 설정, 추후 수정필요
	TMap<FName, TArray<FName>> PlayerCharacterInfo;
	TMap<FName, int32> ItemBoxInfo;
	int32 EnemyCharacterCount = 4;
};
