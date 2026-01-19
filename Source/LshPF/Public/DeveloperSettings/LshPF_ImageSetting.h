// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LshPF_ImageSetting.generated.h"

class UKeyTextureInfo;
/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Image Settings"))
class LSHPF_API ULshPF_ImageSetting : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<UKeyTextureInfo> KeyboardMouseImage;

	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<UKeyTextureInfo> GamepadImage;
};
