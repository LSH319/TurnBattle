// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableButton.h"
#include "LshPF_FocusableCheckBox.generated.h"

DECLARE_DELEGATE_OneParam(IsChangedDelegate, bool);

struct FLshPF_AbilityInfoTableRow;
class UImage;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_FocusableCheckBox : public ULshPF_FocusableButton
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
	
	void InitCheckBox(FLshPF_AbilityInfoTableRow* TargetRow);
	void SetCheckBoxKey(FName NewCheckBoxKey);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor CheckLinearColor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor UnCheckLinearColor;

	bool IsChecked() const;
	FName GetCheckBoxKey() const;

	IsChangedDelegate ChangedDelegate;
protected:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	//~ Begin UUserWidget Interface
	
private:
	bool IsCheck = false;
	FName CheckBoxKey;

	UFUNCTION()
	void OnClickEvent();
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UImage* CheckImage;
	//***** Bound Widgets ***** //
};
