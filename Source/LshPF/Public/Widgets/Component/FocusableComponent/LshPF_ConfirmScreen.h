// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "LshPF_ConfirmScreen.generated.h"

class UDynamicEntryBox;
class UTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class LSHPF_API ULshPF_ConfirmScreen : public ULshPF_FocusableWidgetBase
{
	GENERATED_BODY()

public:
	/**
	 * ConfirmScreen 생성 시 처리하기 위한 함수
	 */
	void InitConfirmScreen(EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EButtonType)> ButtonClickedCallback);

	//~ Begin ULshPF_FocusableWidgetBase Interface
	virtual void WidgetConfirmAction() override;
	virtual void WidgetBackAction() override;
	//~ End ULshPF_FocusableWidgetBase Interface
	
private:
	UFUNCTION()
	void ButtonClickedCallback_Yes();

	UFUNCTION()
	void ButtonClickedCallback_No();
	
	TFunction<void(EButtonType)> CachedCallbackFunction;
	EConfirmScreenType CachedConfirmScreenType;

	FTimerHandle TimerHandle;
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Title;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Message;

	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_Buttons;
	//***** Bound Widgets ***** //
};
