// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_FocusableWidgetBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnWidgetDestroyed, int32);
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_FocusableWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	UWidget* GetDesiredFocusTarget();

	UFUNCTION(BlueprintCallable)
	bool RemoveFromParentStack();

	//~ Begin ULshPF_FocusableWidgetBase Interface
	UFUNCTION(BlueprintCallable)
	virtual void WidgetConfirmAction();
	UFUNCTION(BlueprintCallable)
	virtual void WidgetBackAction();
	//~ End ULshPF_FocusableWidgetBase Interface
	
	FOnWidgetDestroyed OnWidgetDestroyed;
protected:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	//~ End UUserWidget Interface
	
	/** 
	 * Desired Focus Widget 반환.
	 * BP_GetDesiredFocusTarget 함수가 구현되었을 경우 우선적용.
	 *
	 */
	virtual UWidget* NativeGetDesiredFocusTarget();

	/** 
	 * 반환되는 Desired Focus Target 을 이벤트그래프에서 수정하기 위한 함수.
	 *
	 */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Get Desired Focus Target"))
	UWidget* BP_GetDesiredFocusTarget();

	void BeforeDestroyedEvent();
};
