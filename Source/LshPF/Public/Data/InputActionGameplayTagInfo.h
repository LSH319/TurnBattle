// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputActionGameplayTagInfo.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class LSHPF_API UInputActionGameplayTagInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UInputAction* GetInputActionByGameplayTag(const FGameplayTag InFGameplayTag);
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, UInputAction*> InputActionGameplayTagMap;
};
