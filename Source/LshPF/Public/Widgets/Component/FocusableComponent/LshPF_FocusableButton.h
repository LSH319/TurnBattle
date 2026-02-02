// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h" 
#include "LshPF_FocusableButton.generated.h"

class UTextBlock;
class ULshPF_Button;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNaiveTick))
class LSHPF_API ULshPF_FocusableButton : public ULshPF_FocusableWidgetBase
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
	
	UFUNCTION(BlueprintCallable)
	void SetButtonText(UPARAM(ref, DisplayName = "ButtonText") FText Text);
	
private:
	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~ End UUserWidget Interface
	
	//***** Bound Widgets ***** //
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
    ULshPF_Button* ButtonWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;
    //***** Bound Widgets ***** //

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LshPF FocusableButton" ,meta = (AllowPrivateAccess = "true"))
	FText ButtonDisplayText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LshPF FocusableButton", meta = (AllowPrivateAccess = "true"))
	FSlateColor BaseTextSlateColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LshPF FocusableButton", meta = (AllowPrivateAccess = "true"))
	FSlateColor OnFocusTextSlateColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LshPF FocusableButton", meta = (AllowPrivateAccess = "true"))
	FText ButtonDescriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LshPF FocusableButton", meta = (AllowPrivateAccess = "true"))
	FName ViewTargetCameraTag;
};