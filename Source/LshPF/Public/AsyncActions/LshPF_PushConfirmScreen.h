// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "LshPF_PushConfirmScreen.generated.h"

class ULshPF_ConfirmScreen;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmScreenButtonClickedDelegate, EButtonType,
                                            ClickedButtonType);

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_PushConfirmScreen : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = "true", DisplayName = "Push Confirmation Screen"))
	static ULshPF_PushConfirmScreen* PushConfirmScreen(
		const UObject* WorldContextObject,
		TSoftClassPtr<ULshPF_ConfirmScreen> InConfirmScreenClass,
		EConfirmScreenType ScreenType,
		FText InScreenTitle,
		FText InScreenMessage
	);

	//~ Begin UBlueprintAsyncActionBase Interface
	virtual void Activate() override;
	//~ End UBlueprintAsyncActionBase Interface

	UPROPERTY(BlueprintAssignable)
	FOnConfirmScreenButtonClickedDelegate OnButtonClicked;

private:
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	TSoftClassPtr<ULshPF_ConfirmScreen> CachedSoftWidgetClass;
	EConfirmScreenType CachedScreenType;
	FText CachedScreenTitle;
	FText CachedScreenMessage;
};
