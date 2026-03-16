// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Controllers/LshPF_PlayerControllerBase.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "LshPF_Types/LshPF_Structs.h"
#include "LshPF_PlayerController_Battle.generated.h"

class ULshPF_Ability;
class ULshPF_FocusableWidgetBase;
class ULshPF_BattleComponent;
class ILshPF_BattleInterface;
class UInputActionGameplayTagInfo;
class ALshPF_BattleGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetChange, ULshPF_BattleComponent*, TargetBattleComponent);

/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_PlayerController_Battle : public ALshPF_PlayerControllerBase
{
	GENERATED_BODY()

public:
	/*
	 * Button 의 Onclick 에 Bind 될 함수
	 * Tag 에 따라 지정된 로직을 실행
	 * Button 의 Onclick 과 IA 의 동작을 통일하기위해 사용
	 */
	virtual void ExecuteInputActionByGameplayTag(FGameplayTag TargetGameplayTag) override;

	void SetViewTargetToAllTarget();
	
	void SetIsEnableInput(bool InIsEnableInput);
	ETargetType GetTargetType();

	UFUNCTION(BlueprintCallable)
	void SetBattleSettingDefault(bool IsTargetToggleActive);
	void SetTargetTypeWithSetViewTarget(ETargetType InETargetType);

	void AddOnTurnEndRemoveWidget(ULshPF_FocusableWidgetBase* TargetWidget);
	void RemoveOnTurnEndRemoveWidget(ULshPF_FocusableWidgetBase* TargetWidget);
	
	void SetTargetModifier(FBattleAttributeModifier NewTargetModifier);
	FBattleAttributeModifier GetTargetModifier();
	/*
	 * Player Turn 시작 시 Character 에서 호출하여 이벤트 처리를 위한 함수
	 */
	void PlayerCharacterTurnStartEvent();
	void PlayerCharacterTurnEndEvent();
	TArray<ILshPF_BattleInterface*> GetTargetList();

	UFUNCTION(BlueprintCallable)
	ULshPF_BattleComponent* GetTargetBattleComponent();

	UFUNCTION(BlueprintCallable)
	void ResetViewTarget();

	UFUNCTION(BlueprintCallable)
	void SetTargetType(ETargetType InETargetType);
	
	UPROPERTY(BlueprintAssignable)
	FOnTargetChange OnTargetChange;
	
protected:
	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

	//~ Begin APlayerController Interface
	virtual void SetupInputComponent() override;
	//~ End APlayerController Interface

	UFUNCTION(BlueprintPure)
	ALshPF_BattleGameMode* GetBattleGameMode();

	UPROPERTY(EditDefaultsOnly, Category="ItemInfo")
	UDataTable* ItemData;
	
	bool IsEnableInput = false;

	ETargetType TargetType = ETargetType::EnemySingle;
private:
	UPROPERTY()
	ALshPF_BattleGameMode* CachedBattleGameMode;
	
	UPROPERTY()
	AActor* AllTargetViewTarget;

	UPROPERTY()
	TArray<ULshPF_FocusableWidgetBase*> OnTurnEndRemoveWidget;

	UPROPERTY()
	TMap<FName, ULshPF_Ability*> ItemBox;
	
	int32 TargetingEnemyNum = 0;
	int32 TargetingPlayerNum = 0;
	TArray<ILshPF_BattleInterface*> TargetList;
	FBattleAttributeModifier TargetModifier;
	
	/*
	 * FInputActionValue 의 값을 사용하기 위해 IA 에 바인딩 될 함수
	 * ExecuteInputActionByGameplayTag 를 호출하여 Button 과 동작을 통일
	 */
	void ExecuteInputAction(const FInputActionValue& Value, const FGameplayTag TargetGameplayTag);
	
	/*
	 * WidgetStackTag LshPF.WidgetStack 형식의 Tag, Widget 이 추가될 Stack
	 * WidgetTag LshPF.Widget 형식의 Tag, 추가할 Widget 을 표시하는 Tag
	 * IsWidgetGetFocus 추가 된 Widget 이 Focus 를 가질지 여부, Default true
	 */
	void AddWidgetToScreenByTag(FGameplayTag WidgetStackTag, FGameplayTag WidgetTag, bool IsWidgetGetFocus = true);
	void AddSkillScreenToScreen();
	void AddItemScreenToScreen();
	
	/*
	 * TargetList 에 포함된 요소들의 Targeting Toggle을 위한 함수
	 */
	void ToggleTargetingAllTargets(bool IsActive);
	void SetToggleByTargetType(ETargetType InETargetType);
	/*
	 * Index 를 통해 Target Enemy 를 TargetList에 추가
	 * 파라미터를 & 로 받아 값이 배열의 범위를 넘어가도 조정
	 */
	void CachedTargetByIndex(int32& TargetIndex, bool IsTargetEnemy);
	void SetCharacterRotationToTarget();
	
	void Command_Attack();
	void Command_Guard();
	void Command_ChangeTarget_Enemy(bool IsPrev);
	void Command_ChangeTarget_Player(bool IsPrev);
};
