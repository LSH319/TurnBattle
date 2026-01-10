// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_NotFocusableWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_NotFocusableWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	//~ End UUserWidget Interface
};
