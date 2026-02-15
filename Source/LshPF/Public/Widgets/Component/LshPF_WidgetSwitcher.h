// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetSwitcher.h"
#include "LshPF_WidgetSwitcher.generated.h"

class ULshPF_FocusableWidgetBase;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_WidgetSwitcher : public UWidgetSwitcher
{
	GENERATED_BODY()

public:
	/**
	 * 위젯 추가를 위한 함수
	 * @param InSoftWidgetClass WidgetSwitcher 에 추가 할 WidgetClass
	 * @return WidgetSwitcher 에 추가된 WidgetClass
	 */
	UFUNCTION(BlueprintCallable)
	ULshPF_FocusableWidgetBase* AddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass);

protected:
	/**
	 * 위젯 추가를 위한 Native 함수
	 * @param InSoftWidgetClass InSoftWidgetClass WidgetSwitcher 에 추가 할 WidgetClass
	 * @return WidgetSwitcher 에 추가된 WidgetClass
	 */
	ULshPF_FocusableWidgetBase* NativeAddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass);

	/**
	 * 위젯 추가를 위해 블루프린트 로직을 사용할 경우 활용하기 위한 함수
	 * @param InSoftWidgetClass WidgetSwitcher 에 추가 할 WidgetClass
	 * @return WidgetSwitcher 에 추가된 WidgetClass
	 */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add Widget To Stack"))
	ULshPF_FocusableWidgetBase* BP_AddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass);
	
private:
	/**
	 * ChildWidget Destroy 시 처리함수
	 * @param ChildIndex Destroy 되는 ChildWidget 의 ChildIndex
	 */
	UFUNCTION()
	void ChildWidgetDestroyed(int32 ChildIndex);
};
