// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "LshPF_SelectTarget.generated.h"

class ULshPF_Ability;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_SelectTarget : public ULshPF_FocusableWidgetBase
{
	GENERATED_BODY()

public:
	//~ Begin ULshPF_FocusableWidgetBase Interface
	virtual void WidgetConfirmAction() override;
	virtual void WidgetBackAction() override;
	//~ End ULshPF_FocusableWidgetBase Interface
	
	void SetSelectAbility(ULshPF_Ability* SelectedAbility);

private:
	UPROPERTY()
	TWeakObjectPtr<ULshPF_Ability> CachedAbility;
};
