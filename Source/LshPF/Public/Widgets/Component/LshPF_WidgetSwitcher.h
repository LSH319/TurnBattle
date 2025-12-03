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
	UFUNCTION(BlueprintCallable)
	ULshPF_FocusableWidgetBase* AddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass);

protected:
	ULshPF_FocusableWidgetBase* NativeAddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Add Widget To Stack"))
	ULshPF_FocusableWidgetBase* BP_AddWidgetToStack(TSoftClassPtr<ULshPF_FocusableWidgetBase>& InSoftWidgetClass);
};
