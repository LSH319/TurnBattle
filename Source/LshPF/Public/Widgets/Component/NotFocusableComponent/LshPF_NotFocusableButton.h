// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "Widgets/Component/NotFocusableComponent/LshPF_NotFocusableWidgetBase.h"
#include "LshPF_NotFocusableButton.generated.h"

class UInputAction;
class UButton;
class UImage;
class UTextBlock;
class ULshPF_Button;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_NotFocusableButton : public ULshPF_NotFocusableWidgetBase
{
	GENERATED_BODY()

public:
	UButton* GetButton();
	
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText Text);
	
	/**
	 * FGameplayTag 를 통해 버튼에 Bind 될 IA 를 받아 처리
	 * UISubsystem 의 Delegate 에 Bind하는 코드를 포함하므로 여러번 호출 시 주의 필요
	 * InGameplayTag 버튼에 Bind 될 IA 를 검색할 FGameplayTag
	 * return 이미지 등록 성공 여부
	 */
	UFUNCTION(BlueprintCallable)
	bool SetInputActionTag(FGameplayTag InGameplayTag);

	UFUNCTION(BlueprintCallable)
	void BindClickEvent();
	
protected:
	UFUNCTION()
	void RequestExecuteInputActionToController();
	
private:
	FGameplayTag InputActionTag;
	UInputAction* GetInputActionByTag() const;
	
	TWeakObjectPtr<UInputAction> BindInputAction;

	/**
	 * 저장된 IA 에 바인딩 되어있는 Key 확인
	 * key 에 따른 Image 가 저장되어 있는 DataAsset Load
	 * DataAsset Load 후 이미지 저장을 위한 함수 호출
	 * return 이미지 등록 성공 여부
	 */
	bool InitImage();

	/**
	 * CacheTarget 을 Load 후 Image 저장
	 * @param CacheTarget 저장할 Image
	 * @param InKey 바인딩 된 Key
	 */
	void CacheKeyImage(TSoftObjectPtr<UTexture2D> CacheTarget, FKey InKey);

	/**
	 * UISubsystem 에 InputDevice 요청
	 * InputDevice 에 따른 Image 설정 함수 호출
	 */
	void ChangeImageWithInputDeviceType();

	/**
	 * RecentlyInputDeviceType 에 따라 Image 변경
	 * @param RecentlyInputDeviceType Image 설정을 위한 InputDevice
	 */
	UFUNCTION()
	void RecentlyInputDeviceChangedCallback(EInputDeviceType RecentlyInputDeviceType);
	
	UPROPERTY()
	UTexture2D* CachedKeyboardImage;
	UPROPERTY()
	UTexture2D* CachedGamepadImage;
	
	//***** Bound Widgets ***** //
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess))
	ULshPF_Button* ButtonWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	UPROPERTY(meta = (BindWidget))
	UImage* ButtonImage;
	//***** Bound Widgets ***** //
};
