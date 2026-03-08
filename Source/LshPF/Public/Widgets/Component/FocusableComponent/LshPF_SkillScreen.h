// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "LshPF_SkillScreen.generated.h"

class UTextBlock;
class ULshPF_ListView;
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
	//~ Begin ULshPF_FocusableWidgetBase Interface
	virtual void WidgetConfirmAction() override;
	//~ End ULshPF_FocusableWidgetBase Interface
	
	void InitAbilityList(TArray<ULshPF_Ability*> CharacterAbilityList);

	UFUNCTION(BlueprintPure)
	UListView* GetSkillScreenListView();

protected:
	virtual void BeforeDestroyedEvent() override;
	
private:
	UFUNCTION()
	void DescriptionTextUpdate(FText DescriptionText);
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	ULshPF_ListView* AbilityList;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_AbilityDescription;
	//***** Bound Widgets ***** //
};
