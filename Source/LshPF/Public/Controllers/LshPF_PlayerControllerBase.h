// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LshPF_PlayerControllerBase.generated.h"

class UButton;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	TSoftObjectPtr<UInputAction> GetDefaultConfirmAction();
	TSoftObjectPtr<UInputAction> GetDefaultBackAction();
	TArray<FKey> GetKeysByInputAction(const UInputAction* InAction);
	
protected:
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> InputDeviceCheckMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> InputDeviceCheckAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> DefaultConfirmAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> DefaultBackAction;
	
	void DefaultConfirmAction_Callback();
	void DefaultBackAction_Callback();
	void InputDeviceCheckAction_Callback();
};
