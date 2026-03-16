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
	int32 GetAllCharacterCount() const;

	TArray<FName> GetPlayerCharacterKeyNames() const;
	int32 GetEnemyCharacterCount() const;
	
	void SetEnemyCharacterCount(int32 NewEnemyCharacterCount);
	
	TMap<FName, int32> GetItemBoxInfo();

protected:
	void SetItemBoxForTest();
	
private:
	//todo : test 를 위해 설정, 추후 수정필요
	TArray<FName> PlayerCharacterKeyNames = {"001","002","003","004"};
	TMap<FName, int32> ItemBoxInfo;
	int32 EnemyCharacterCount = 4;
};
