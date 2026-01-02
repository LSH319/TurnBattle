// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "MyLshPF_FocusableButton.generated.h"

class UTextBlock;
class ULshPF_Button;
/**
 * 
 */
UCLASS()
class LSHPF_API UMyLshPF_FocusableButton : public ULshPF_FocusableWidgetBase
{
	GENERATED_BODY()
public:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	//~ End UUserWidget Interface

	UFUNCTION(BlueprintCallable)
	void SetButtonText(UPARAM(ref, DisplayName = "ButtonText") FText& Text);
	
private:
	//***** Bound Widgets ***** //
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
    ULshPF_Button* ButtonWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;
    //***** Bound Widgets ***** //

	UFUNCTION()
	void OnButtonClicked();
};
