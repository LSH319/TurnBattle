// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "KeyTextureInfo.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API UKeyTextureInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UTexture2D* GetTextureByKey(FKey InKey);
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FKey, UTexture2D*> KeyTextureMap;
};
