// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "UObject/NoExportTypes.h"
#include "LshPF_Ability.generated.h"

class ALshPF_PlayerController_Battle;
class ALshPF_BattleGameMode;
class ULshPF_BattleComponent;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_Ability : public UObject
{
	GENERATED_BODY()

public:
	/*
	 * Ability 를 소유하고 있는 BattleComponent 설정
	 */
	void SetOwnerBattleComponent(ULshPF_BattleComponent* OwnerBattleComponentPointer);
	/*
	 * AbilityKey 를 통해 Ability 의 내부 Data 초기화
	 */
	void InitAbilityData(FName AbilityKey);
	/*
	 * AbilityCost 와 실제 값을 비교해 사용 가능여부 반환
	 */
	bool IsCanActivate();
	/*
	 * Ability 사용을 위해 호출될 함수
	 */
	void CommitAbility();

protected:
	/*
	 * Display 등에 사용될 Text
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	FText AbilityName;

	/*
	 * Modifier Value 계산 시 사용 할 Attribute
	 * DamageRatioAttributeType * DamageRatio
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EAttributeType DamageRatioAttributeType = EAttributeType::Unknown;

	/*
	 * Modifier Value 계산 시 사용 할 Ratio
	 * DamageRatioAttributeType * DamageRatio
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	float DamageRatio = 0.f;

	/*
	 * Modifier Value 를 적용할 Attribute
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EAttributeType TargetAttributeType = EAttributeType::Unknown;

	/*
	 * Ability 사용 시 요구하는 Cost 의 Attribute
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EAttributeType CostAttributeType = EAttributeType::Unknown;

	/*
	 * Ability 사용 시 요구하는 Cost
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	float AbilityCost = 0.f;

	/*
	 * Ability 사용 시 Target 관련 정보
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	ETargetType TargetType = ETargetType::Unknown;

	/*
	 * Modifier 타입에 대한 정보
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EModifierType AbilityType = EModifierType::Unknown;

	/*
	 * Ability 사용 시 실제 로직
	 */
	virtual void ActivateAbility();

	/*
	 * AbilityType 에 따라 TargetBattleComponents 를 반환
	 */
	TArray<ULshPF_BattleComponent*> GetTargetBattleComponents();
	
	ALshPF_BattleGameMode* GetBattleGameMode();
	ALshPF_PlayerController_Battle* GetBattlePlayerController();
	
private:
	UPROPERTY()
	TWeakObjectPtr<ALshPF_BattleGameMode> CachedBattleGameMode;

	UPROPERTY()
	TWeakObjectPtr<ALshPF_PlayerController_Battle> CachedPlayerController;
	
	UPROPERTY()
	TWeakObjectPtr<ULshPF_BattleComponent> OwnerBattleComponent;
};
