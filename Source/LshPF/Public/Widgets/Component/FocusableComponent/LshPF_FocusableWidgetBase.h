// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_FocusableWidgetBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnWidgetDestroyed, int32);

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class LSHPF_API ULshPF_FocusableWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** 
	 * Desired Focus Widget 반환
	 */
	UFUNCTION(BlueprintCallable)
	UWidget* GetDesiredFocusTarget();

	/** 
	 * Widget 이 저장된 Widget Switcher 에서 제거
	 */
	UFUNCTION(BlueprintCallable)
	bool RemoveFromParentStack();

	//~ Begin ULshPF_FocusableWidgetBase Interface
	/**
	 * Default Confirm IA 입력시 호출 될 함수
	 * 입력시 처리가 필요할 경우 override 하여 사용
	 */
	UFUNCTION(BlueprintCallable)
	virtual void WidgetConfirmAction();
	/**
	 * Default Back IA 입력시 호출 될 함수
	 * 입력시 처리가 필요할 경우 override 하여 사용
	 */
	UFUNCTION(BlueprintCallable)
	virtual void WidgetBackAction();
	//~ End ULshPF_FocusableWidgetBase Interface
	
	FOnWidgetDestroyed OnWidgetDestroyed;

	//Child Widget 이 Focus 흭득 시 해당 위젯을 저장해두기 위한 Delegate
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusWidgetChanged, ULshPF_FocusableWidgetBase*)
	FOnFocusWidgetChanged OnFocusWidgetChanged;
	
protected:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
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

	/**
	 * Child Widget 이 Focus 흭득시와 관련된 처리를 위한 함수
	 * Widget 의 구성요소 중 Focus 를 받을 수 있는 Widget 들에 대해 호출 필요 
	 * @param InFocusTargetWidget Focus 를 받을 수 있는 Widget
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Bind Child Widget Get Focus"))
	void BP_BindChildWidgetGetFocus(ULshPF_FocusableWidgetBase* InFocusTargetWidget);

	/**
	 * Destroy 전 처리해야 할 이벤트들
	 */
	void BeforeDestroyedEvent();

	/**
	 * UISubsystem 에 InputDevice update 요청
	 */
	void UpdateInputDevice();

	/**
	 * Widget 의 구성요소 중 Focus 를 받을 Widget
	 */
	UPROPERTY(BlueprintReadOnly)
	ULshPF_FocusableWidgetBase* DesiredFocusTarget;

private:
	UFUNCTION()
	void SetDesiredFocusTarget(ULshPF_FocusableWidgetBase* InFocusTargetWidget);
};
