// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "LshPF_WidgetMapSetting.generated.h"

class ULshPF_FocusableWidgetBase;
/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Widget Map Settings"))
class LSHPF_API ULshPF_WidgetMapSetting : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Map", meta = (ForceInlineRow, Categories = "LshPF.Widget"))
	TMap<FGameplayTag, TSoftClassPtr<ULshPF_FocusableWidgetBase>> LshPF_WidgetMap;
};
