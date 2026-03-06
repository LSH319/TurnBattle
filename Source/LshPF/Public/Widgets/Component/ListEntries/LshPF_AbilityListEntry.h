// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/ListEntries/LshPF_ListEntryBase.h"
#include "LshPF_AbilityListEntry.generated.h"

class UImage;
class UTextBlock;
class ULshPF_Ability;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_AbilityListEntry : public ULshPF_ListEntryBase
{
	GENERATED_BODY()

public:
	//~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	//~ End IUserObjectListEntry Interface
	
protected:
	void InitListEntryData(ULshPF_Ability* AbilityData);

	UPROPERTY(EditDefaultsOnly)
	FSlateBrush DefaultBackgroundBrush;
	UPROPERTY(EditDefaultsOnly)
	FSlateBrush OnFocusBackgroundBrush;
	
private:
	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~ End UUserWidget Interface
	
	FText GetDescriptionText(ULshPF_Ability* AbilityData);

	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UImage* Background;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_AbilityName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_CostType;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Cost;
	//***** Bound Widgets ***** //
};
