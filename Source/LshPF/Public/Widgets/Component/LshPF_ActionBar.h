// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_ActionBar.generated.h"

class UInputAction;
class UDynamicEntryBox;

USTRUCT(BlueprintType)
struct FActionBarEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag InputActionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText EntryText;

	UPROPERTY(EditAnywhere)
	bool IsNeedBindClick = false;
};

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_ActionBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool ShowDefaultConfirmAction = false;

	UPROPERTY(EditAnywhere)
	bool ShowDefaultBackAction = false;

	UPROPERTY(EditAnywhere)
	TArray<FActionBarEntry> ActionBarEntry;

	/*
	 * ActionBar 에 Entry 추가
	 * return 이미지 설정 실패
	 */
	UFUNCTION(BlueprintCallable)
	bool CreateActionBarEntry();
	
protected:
	//~ Begin UUserWidget interface
	virtual void NativeConstruct() override;
	//~ Begin UUserWidget interface

private:
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* ActionBar;
	//***** Bound Widgets ***** //
};
