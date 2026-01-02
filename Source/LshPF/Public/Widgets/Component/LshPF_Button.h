// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "LshPF_Button.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_Button : public UButton
{
	GENERATED_BODY()

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface
};
