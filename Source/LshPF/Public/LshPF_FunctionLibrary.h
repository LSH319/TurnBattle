// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LshPF_FunctionLibrary.generated.h"

class ULshPF_FocusableWidgetBase;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "LshP Function Library")
	static TSoftClassPtr<ULshPF_FocusableWidgetBase> GetSoftFocusableWidgetBaseClassByTag(UPARAM(meta = (Categories = "LshPF.Widget")) FGameplayTag InWidgetTag);
};
