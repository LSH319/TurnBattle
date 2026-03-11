// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableWidgetBase.h"
#include "LshPF_NotFocusableWidget_Status.generated.h"

class UTextBlock;
class ULshPF_BattleComponent;
class UProgressBar;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_NotFocusableWidget_Status : public ULshPF_NotFocusableWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetBattleComponent(ULshPF_BattleComponent* BattleComponent);

private:
	UPROPERTY()
	ULshPF_BattleComponent* CachedBattleComponent;

	UFUNCTION()
	void AttributeChangedCallback(EAttributeType AttributeType, float NewAttribute);
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;
	//***** Bound Widgets ***** //
};
