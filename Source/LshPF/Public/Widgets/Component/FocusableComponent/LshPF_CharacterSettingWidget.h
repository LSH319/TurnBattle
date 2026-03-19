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
	/*
	 * 내부 위젯들의 데이터를 취합해 GameInatance 의 PlayerCharacterInfo 를 설정
	 * return : 사용 캐릭터가 Empty 일 경우 False
	 */
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
