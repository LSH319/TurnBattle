// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_NotFocusableWidgetBase.generated.h"

class ALshPF_PlayerControllerBase;
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

	/**
	 * GetOwningPlayer 를 ALshPF_PlayerControllerBase 로 캐스팅 하여 return
	 * @return GetOwningPlayer 를 ALshPF_PlayerControllerBase 로 캐스팅한 결과물
	 */
	ALshPF_PlayerControllerBase* GetLshPF_PlayerController();
};
