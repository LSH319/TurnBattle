// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/LshPF_WidgetInterface.h"
#include "LshPF_Rotator_Int.generated.h"

class ULshPF_FocusableButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValueChangeEvent, int, NewValue, FName, RotatorKey);

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_Rotator_Int : public UUserWidget, public ILshPF_WidgetInterface
{
	GENERATED_BODY()
public:
	//~ Begin ILshPF_WidgetInterface Interface
	virtual void WidgetConfirmAction() override;
	virtual void WidgetBackAction() override;
	//~ End ILshPF_WidgetInterface Interface
	
	UPROPERTY(BlueprintAssignable)
	FOnValueChangeEvent OnValueChangeEvent;

	UPROPERTY(EditAnywhere, Category = "Rotator/Value")
	int32 MinValue = 0;

	UPROPERTY(EditAnywhere, Category = "Rotator/Value")
	int32 MaxValue = 4;

	UPROPERTY(BlueprintReadOnly, Category = "Rotator/Value")
	int32 CurrentValue = 0;

	UPROPERTY(EditAnywhere, Category = "Rotator")
	FSlateColor DefaultTextColor;

	UPROPERTY(EditAnywhere, Category = "Rotator")
	FSlateColor FocusTextColor;

	UPROPERTY(EditAnywhere, Category = "Rotator")
	UTexture2D* PreviousTexture;

	UPROPERTY(EditAnywhere, Category = "Rotator")
	UTexture2D* NextTexture;
	
	UPROPERTY(EditDefaultsOnly, Category = "Rotator/Key")
	TArray<FKey> PreviousKey;

	UPROPERTY(EditDefaultsOnly, Category = "Rotator/Key")
	TArray<FKey> NextKey;

	UFUNCTION(BlueprintCallable)
	void SetRotatorTitle(FText NewText);

	UFUNCTION(BlueprintCallable)
	void SetRotatorValue(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetRotatorKey(FName NewKey);
	
protected:
	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual FReply NativeOnPreviewKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	//~ End UUserWidget Interface
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RotatorTitle;
	
	UPROPERTY(meta = (BindWidget))
	ULshPF_FocusableButton* PreviousButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RotatorValue;
	
	UPROPERTY(meta = (BindWidget))
	ULshPF_FocusableButton* NextButton;
	//***** Bound Widgets ***** //

private:
	UFUNCTION()
	void OnValueAddEvent();
	UFUNCTION()
	void OnValueSubEvent();

	FName RotatorKey = "";
};
