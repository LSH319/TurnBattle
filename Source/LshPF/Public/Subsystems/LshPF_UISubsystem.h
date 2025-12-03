// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LshPF_UISubsystem.generated.h"

class ULshPF_FocusableWidgetBase;
class ULshPF_PrimaryLayout;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_UISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static ULshPF_UISubsystem* Get(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(ULshPF_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<ULshPF_FocusableWidgetBase> InSoftWidgetClass, TFunction<void(ULshPF_FocusableWidgetBase*)> AsyncPushStateCallback);
	
private:
	UPROPERTY()
	ULshPF_PrimaryLayout* CreatedPrimaryLayout;
};
