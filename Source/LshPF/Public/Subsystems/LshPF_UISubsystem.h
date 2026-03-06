// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LshPF_UISubsystem.generated.h"

class ULshPF_BattleComponent;
enum class EHardwareDevicePrimaryType : uint8;
struct FHardwareDeviceIdentifier;
class ULshPF_ConfirmScreen;
class UWidget;
class ULshPF_FocusableWidgetBase;
class ULshPF_PrimaryLayout;

DECLARE_DELEGATE(FFindNewFocusWidget)
DECLARE_MULTICAST_DELEGATE_OneParam(FInputDeviceChange, EInputDeviceType)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBattleComponentDelegate, ULshPF_BattleComponent*, BattleComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonDescriptionTextUpdatedDelegate, FText, DescriptionText);

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_UISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static ULshPF_UISubsystem* Get(const UObject* WorldContextObject);
	
	/**
	 * PrimaryLayoutWidget 을 UISubsystem 에 저장
	 * @param InCreatedWidget 생성된 PrimaryLayoutWidget
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UPARAM(meta = (Categories = "LshPF.WidgetStack")) ULshPF_PrimaryLayout* InCreatedWidget);

	/**
	 * InWidgetStackTag 를 통해 Widget 이 추가될 WidgetSwitcher 지정
	 * 지정된 WidgetSwitcher 에 Widget 을 추가
	 * @param InWidgetStackTag WidgetSwitcher 탐색을 위한 Tag
	 * @param InSoftWidgetClass 추가할 Widget Class
	 * @param AsyncPushStateCallback 위젯 추가 후 호출될 함수
	 */
	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag, TSoftClassPtr<ULshPF_FocusableWidgetBase> InSoftWidgetClass, TFunction<void(ULshPF_FocusableWidgetBase*)> AsyncPushStateCallback);

	/**
	 * ConfirmScreen 추가를 위한 함수
	 * ConfirmScreen 은 가장 전면의 WidgetSwitcher 에 추가
	 * @param InConfirmScreenClass 추가할 Widget Class
	 * @param InScreenType ConfirmScreen 의 Button 생성시 Type
	 * @param InScreenTitle ConfirmScreen 의 Title Text
	 * @param InScreenMsg ConfirmScreen 의 Msg
	 * @param ButtonClickedCallback 위젯 추가 후 호출될 함수
	 */
	void PushConfirmScreen(TSoftClassPtr<ULshPF_ConfirmScreen> InConfirmScreenClass, EConfirmScreenType InScreenType, const FText& InScreenTitle, const FText& InScreenMsg, TFunction<void(EButtonType)> ButtonClickedCallback);

	EInputDeviceType GetRecentlyInputDeviceType();
	/**
	 * InputDeviceType 을 직접 전달하여 설정
	 */
	void SetRecentlyInputDeviceType(EInputDeviceType InRecentlyInputDeviceType);
	/**
	 * InputDeviceType 을 UISubsystem 에서 확인해서 사용
	 */
	UFUNCTION(BlueprintCallable)
	void SetRecentlyInputDeviceType();

	/**
	 * PrimaryLayoutWidget 에서 Focus 를 받아야 하는 Widget 을 탐색하여 반환
	 * @return Focus 를 받아야 하는 Widget
	 */
	UWidget* GetFocusTargetWidget();

	void SetWidgetSwitcherVisibilityWithTag(UPARAM(meta = (Categories = "LshPF.WidgetStack")) FGameplayTag InTag, ESlateVisibility Visibility);

	//Focus Widget 재탐색 관련 Delegate
	FFindNewFocusWidget FindNewFocusWidget;
	//Input Device 변경 관련 Delegate
 	FInputDeviceChange InputDeviceChange;
	//Description Text 변경을 위한 Delegate
	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;
	//Broadcast 시 해당 Component 에 따른 Status Widget 생성 을 위한 Delegate
	UPROPERTY(BlueprintAssignable)
	FOnBattleComponentDelegate OnBattleComponentDelegate;
	
private:
	EInputDeviceType RecentlyInputDeviceType = EInputDeviceType::KeyboardAndMouse;
	
	UPROPERTY()
	ULshPF_PrimaryLayout* CreatedPrimaryLayout;
};
