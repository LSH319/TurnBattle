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

	int32 GetPlayerCharacterCount() const;
	int32 GetEnemyCharacterCount() const;
	
	void SetPlayerCharacterCount(int32 NewPlayerCharacterCount);
	void SetEnemyCharacterCount(int32 NewEnemyCharacterCount);

private:
	//todo : test 를 위해 설정, 추후 수정필요
	int32 PlayerCharacterCount = 2;
	int32 EnemyCharacterCount = 3;
};
