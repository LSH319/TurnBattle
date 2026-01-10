// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LshPF_UISubsystem.generated.h"

class ULshPF_ConfirmScreen;
class UWidget;
DECLARE_DELEGATE(FFindNewFocusWidget)

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
	void PushConfirmScreen(TSoftClassPtr<ULshPF_ConfirmScreen> InConfirmScreenClass, EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EButtonType)> ButtonClickedCallback);
	
	UWidget* GetFocusTargetWidget();
	
	FFindNewFocusWidget FindNewFocusWidget;
	
private:
	UPROPERTY()
	ULshPF_PrimaryLayout* CreatedPrimaryLayout;
};
