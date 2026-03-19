// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "LshPF_CharacterCheckList.generated.h"

class UImage;
struct FPlayerBattleCharacterInfo;
class ULshPF_FocusableCheckBox;
class UDynamicEntryBox;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_CharacterCheckList : public ULshPF_FocusableWidgetBase
{
	GENERATED_BODY()
	
public:
	//~ Begin UUserWidget Interface
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	//~ End UUserWidget Interface
	
	//~ Begin ULshPF_FocusableWidgetBase Interface
	virtual void WidgetConfirmAction() override;
	virtual void WidgetBackAction() override;
	//~ End ULshPF_FocusableWidgetBase Interface

	void SetTargetCharacter(FName CharacterKey, FPlayerBattleCharacterInfo CharacterInfo);

	UFUNCTION(BlueprintCallable)
	ULshPF_FocusableCheckBox* GetIsCharacterUse() const;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor OnFocusBackgroundColor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor DefaultBackgroundColor;

	TTuple<FName, TArray<FName>> GetTargetCharacterInfo();
	bool IsTargetCharacterUse() const;
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, Category="AbilityInfo")
	UDataTable* AbilityData;
private:
	FName TargetCharacterKey;
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;
	
	UPROPERTY(meta = (BindWidget))
	ULshPF_FocusableCheckBox* IsCharacterUse;
		
	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_SkillSetting;
	//***** Bound Widgets ***** //
};
