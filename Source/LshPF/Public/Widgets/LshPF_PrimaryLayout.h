// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_PrimaryLayout.generated.h"

class ULshPF_WidgetSwitcher;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_PrimaryLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	ULshPF_WidgetSwitcher* FindWidgetSwitcherByTag(const FGameplayTag InTag);
	
protected:
	//~ Begin UUserWidget Interface
    virtual void NativeConstruct() override;
    //~ Begin UUserWidget Interface
	
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetSwitcher(UPARAM(meta = (Categories = "LshPF.WidgetStack")) FGameplayTag InTag, ULshPF_WidgetSwitcher* InSwitcher);

	
private:
	UFUNCTION()
	void SetFocusToPriorityWidget();
	
	UPROPERTY()
	TMap<FGameplayTag, ULshPF_WidgetSwitcher*> RegisterWidgetSwitcherMap;

	UPROPERTY()
	TArray<FGameplayTag> TagPriorityArray;
};