// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "LshPF_ShowTextWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_ShowTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetApplyText(const FString& Text, bool IsDamage);
};
