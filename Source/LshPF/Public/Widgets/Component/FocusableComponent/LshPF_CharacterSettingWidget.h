// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "LshPF_CharacterSettingWidget.generated.h"

class ULshPF_FocusableButton;
class UDynamicEntryBox;
class UPlayerCharacterInfo;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_CharacterSettingWidget : public ULshPF_FocusableWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool SetPlayerCharacterInfoInInstance();
	
protected:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	//~ End UUserWidget Interface
	
	UPROPERTY(EditDefaultsOnly)
	UPlayerCharacterInfo* CharacterInfo;

	//***** Bound Widgets ***** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_CharacterSetting;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	ULshPF_FocusableButton* NextButton;
	//***** Bound Widgets ***** //
};
