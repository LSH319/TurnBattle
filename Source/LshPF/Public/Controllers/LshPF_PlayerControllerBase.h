// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "LshPF_PlayerControllerBase.generated.h"

class UInputActionGameplayTagInfo;
struct FInputActionValue;
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
	/*
	 * Tag 와 관련해 IA 사용시 override 하여 사용
	 */
	UFUNCTION(BlueprintCallable)
	virtual void ExecuteInputActionByGameplayTag(FGameplayTag TargetGameplayTag);
	
	TArray<FKey> GetKeysByInputAction(const UInputAction* InAction);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual UInputAction* GetInputActionByGameplayTag(FGameplayTag TargetGameplayTag);
	
protected:
	//~ Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	//~ End APlayerController Interface
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input/Data")
	UInputActionGameplayTagInfo* InputActionGameplayTagInfo;

	void DefaultConfirmAction_Callback();
	void DefaultBackAction_Callback();
	void InputDeviceCheckAction_Callback();
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputDeviceCheckMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InputDeviceCheckAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* DefaultConfirmAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* DefaultBackAction;
};
