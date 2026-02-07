// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_PrimaryLayout.generated.h"

class ULshPF_WidgetSwitcher;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_PrimaryLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * RegisterWidgetSwitcherMap 에 등록되어 있는 WidgetSwitcher 탐색
	 * @param InTag 탐색하기 원하는 WidgetSwitcher 의 FGameplayTag
	 * @return InTag 를 통해 찾아낸 WidgetSwitcher
	 */
	ULshPF_WidgetSwitcher* FindWidgetSwitcherByTag(const FGameplayTag InTag);
	
	/**
	 * WidgetSwitcher 내부에 있는 Widget 중 Focus를 받아야 하는 Widget을 return
	 * @return Focus를 받아야 하는 Widget
	 */
	UWidget* GetFocusTargetInFocusWidgetSwitcher();
	
protected:
	//~ Begin UUserWidget Interface
    virtual void NativeConstruct() override;
    //~ End UUserWidget Interface

	/**
	 * GameplayTag 와 WidgetSwitcher 를 받아 RegisterWidgetSwitcherMap 에 저장
	 * 탐색 시 늦게 등록된 요소를 우선 탐색
	 * @param InTag Key 로 사용할 FGameplayTag
	 * @param InSwitcher Value 로 사용할 WidgetSwitcher
	 */
	UFUNCTION(BlueprintCallable)
	void RegisterWidgetSwitcher(UPARAM(meta = (Categories = "LshPF.WidgetStack")) FGameplayTag InTag, ULshPF_WidgetSwitcher* InSwitcher);

private:
	/**
	 * 우선 순위에 따라 RegisterWidgetSwitcherMap 를 탐색해 Active Widget 이 있는 WidgetSwitcher 중 우선순위가 가장 높은 WidgetSwitcher 반환
	 * @return Active Widget 이 있는 WidgetSwitcher 중 우선순위가 가장 높은 WidgetSwitcher
	 */
	ULshPF_WidgetSwitcher* FindFocusWidgetSwitcher();
	
	/**
	 * WidgetSwitcher 의 Active Widget 이 Focus Target 으로 삼은 Widget 을 반환
	 * @param InWidgetSwitcher Active Widget 을 찾을 WidgetSwitcher
	 * @return Active Widget 에서 설정한 Focus Target Widget
	 */
	UWidget* GetFocusTargetInWidgetSwitcher(ULshPF_WidgetSwitcher* InWidgetSwitcher);

	/**
	 * Focus 를 받아야 하는 Widget 에 Focus 설정
	 * RegisterWidgetSwitcherMap 를 우선순위에 따라 탐색, 탐색된 Active Widget 의 Focus Target 에 Focus 설정
	 */
	UFUNCTION()
	void SetFocusToPriorityWidget();

	//WidgetSwitcher 저장을 위한 Map
	UPROPERTY()
	TMap<FGameplayTag, ULshPF_WidgetSwitcher*> RegisterWidgetSwitcherMap;

	// Tag 를 통해 탐색 순서를 정하기 위한 Array
	UPROPERTY()
	TArray<FGameplayTag> TagPriorityArray;
};