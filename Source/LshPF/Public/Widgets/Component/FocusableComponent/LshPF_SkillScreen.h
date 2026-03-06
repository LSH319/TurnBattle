// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "LshPF_SkillScreen.generated.h"

class ULshPF_Ability;
class UListView;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_SkillScreen : public ULshPF_FocusableWidgetBase
{
	GENERATED_BODY()
	
public:
	void InitAbilityList(TArray<ULshPF_Ability*> CharacterAbilityList);

	UFUNCTION(BlueprintPure)
	UListView* GetSkillScreenListView();
	
private:
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UListView* AbilityList;
	//***** Bound Widgets ***** //
};
