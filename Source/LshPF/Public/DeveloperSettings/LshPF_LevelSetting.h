// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "LshPF_LevelSetting.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Level Settings"))
class LSHPF_API ULshPF_LevelSetting : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "Level Map", meta = (ForceInlineRow, Categories = "LshPF.Level"))
	TMap<FGameplayTag, TSoftObjectPtr<UWorld>> LshPF_LevelMap;
};
