// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_FocusableWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_FocusableWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UWidget* GetDesiredFocusWidget();
	
protected:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	//~ Begin UUserWidget Interface
	
	/** 
	 * Desired Focus Widget 반환.
	 * BP_GetDesiredFocusWidget 함수가 구현되었을 경우 우선적용.
	 *
	 */
	virtual UWidget* NativeGetDesiredFocusWidget();

	/** 
	 * 반환되는 Desired Focus Widget 을 이벤트그래프에서 수정하기 위한 함수.
	 *
	 */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Desired Focus Widget"))
	UWidget* BP_GetDesiredFocusWidget();
};
