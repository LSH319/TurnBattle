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

	/*
	 * Table Row 를 받아 위젯 초기화
	 */
	void InitCheckBox(FLshPF_AbilityInfoTableRow* TargetRow);
	/*
	 * 체크 박스가 가르키는 목표 Key
	 */
	void SetCheckBoxKey(FName NewCheckBoxKey);
	/*
	 * 체크박스 체크 여부 설정
	 */
	void SetIsCheck(bool InIsCheck);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor CheckLinearColor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor UnCheckLinearColor;

	bool IsChecked() const;
	FName GetCheckBoxKey() const;

	/*
	 * Check 여부 변경시 사용할 Delegate
	 */
	IsChangedDelegate ChangedDelegate;
protected:
	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	//~ Begin UUserWidget Interface
	
private:
	bool IsCheck = false;
	FName CheckBoxKey;

	/*
	 * 체크박스 상호작용 함수
	 */
	UFUNCTION()
	void OnClickEvent();
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UImage* CheckImage;
	//***** Bound Widgets ***** //
};
