// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableWidgetBase.h"
#include "LshPF_NotFocusableButton.generated.h"

class UButton;
class UImage;
class UTextBlock;
class ULshPF_Button;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_NotFocusableButton : public ULshPF_NotFocusableWidgetBase
{
	GENERATED_BODY()

public:
	UButton* GetButton();

	void SetButtonText(FText Text);

	void SetButtonType(EButtonType InButtonType);
	EButtonType GetButtonType();
	
private:
	EButtonType ButtonType = EButtonType::Unknown; 
	
	//***** Bound Widgets ***** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	ULshPF_Button* ButtonWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	UPROPERTY(meta = (BindWidget))
	UImage* ButtonImage;
	//***** Bound Widgets ***** //
};
