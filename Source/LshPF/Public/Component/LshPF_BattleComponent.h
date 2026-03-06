// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "LshPF_BattleComponent.generated.h"

class ULshPF_Ability;
class ILshPF_BattleInterface;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamageDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedDelegate, EAttributeType, float);

USTRUCT(BlueprintType)
struct FBattleAttributeModifier
{
	GENERATED_BODY()

	FBattleAttributeModifier()
	:TargetAttribute(EAttributeType::Unknown), ModifierType(EModifierType::Damage_Default)
	{}
	
	FBattleAttributeModifier(float InModifyValue, EAttributeType InAttributeType, EModifierType InModifierType)
	:ModifyValue(InModifyValue), IsCritical(false), TargetAttribute(InAttributeType), ModifierType(InModifierType)
	{
	}

	//변경할 값
	UPROPERTY()
	float ModifyValue = 0;

	//크리티컬 여부
	UPROPERTY()
	bool IsCritical = false;

	//변경할 Attribute
	UPROPERTY()
	EAttributeType TargetAttribute;
	
	UPROPERTY()
	EModifierType ModifierType;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LSHPF_API ULshPF_BattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/*
	* Target 에게 Modifier 적용
	* ModifierActorBattleComponent Modifier를 받는 Actor BattleComponent
	* CauserBattleComponent Modifier를 가하는 Actor BattleComponent
	* BattleAttributeModifier Modifier 관련 정보
	* return : 실제 Target 에 적용된 Value
	 */
	UFUNCTION(BlueprintCallable)
	float ApplyModifierToTarget(ULshPF_BattleComponent* ModifierActorBattleComponent, ULshPF_BattleComponent* CauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier);

	/*
	* Target 에게 Damage 적용
	* DamagedActorBattleComponent Damage를 받는 Actor BattleComponent
	* DamageCauserBattleComponent Damage를 가하는 Actor BattleComponent
	* BattleAttributeModifier Damage 관련 정보
	* return : 실제 Target 에 적용된 Damage
	 */
	UFUNCTION(BlueprintCallable)
	float ApplyDamageToTarget(ULshPF_BattleComponent* DamagedActorBattleComponent, ULshPF_BattleComponent* DamageCauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier);

	/*
	* Target 에게 Cure 적용
	* CuredActorBattleComponent Cure 받는 Actor BattleComponent
	* HealCauserBattleComponent Cure 가하는 Actor BattleComponent
	* BattleAttributeModifier Cure 관련 정보
	* return : 실제 Target 에 적용된 Cure
	 */
	UFUNCTION(BlueprintCallable)
	float ApplyCureToTarget(ULshPF_BattleComponent* CuredActorBattleComponent, ULshPF_BattleComponent* HealCauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier);

	/*
	 * Damage 받을경우 처리
	 * DamageCauserBattleComponent Damage를 가하는 Actor BattleComponent
	 * BattleAttributeModifier Damage 관련 정보
	 * return : 실제 적용된 Damage
	 */
	UFUNCTION(BlueprintCallable)
	float TakeDamageFromCursor(ULshPF_BattleComponent* DamageCauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier);

	/*
	 * Cure 받을경우 처리
	 * CureCauserBattleComponent Cure를 가하는 Actor BattleComponent
	 * BattleAttributeModifier Cure 관련 정보
	 * return : 실제 적용된 Cure
	 */
	UFUNCTION(BlueprintCallable)
	float TakeCureFromCursor(ULshPF_BattleComponent* CureCauserBattleComponent, FBattleAttributeModifier BattleAttributeModifier);

	/*
	 * EAttributeType 에 따른 Attribute 값 반환
	 * AttributeType 원하는 Attribute 값
	 * return : EAttributeType 에 따른 Attribute 값
	 */
	UFUNCTION(BlueprintCallable)
	float GetAttribute(EAttributeType AttributeType); 

	/*
	 * EAttributeType 에 따른 Attribute 값을 NewAttribute 값으로 설정
	 * AttributeType 원하는 Attribute 값
	 * NewAttribute 변경하길 원하는 값
	 */
	UFUNCTION(BlueprintCallable)
	void SetAttribute(EAttributeType AttributeType, float NewAttribute);
	
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamageDelegate OnTakeDamageDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamageDelegate OnTakeHealDelegate;

	FOnAttributeChangedDelegate AttributeChangedDelegate;
	
	/*
	 * Attribute 변경에 필요한 정보를 담고있는 구조체 생성
	 * TargetAttributeType 변경을 원하는 Attribute
	 * BaseAttributeType 변경 할 값을 계산할때 사용할 Attribute
	 * DamageRatio 변경 할 값을 계산할때 사용할 배율
	 * ex.
	 * TargetAttributeType = EAttributeType::CurrentHealth, BaseAttributeType = EAttributeType::CurrentAttack, DamageRatio = 1 인경우
	 * Target 의 EAttributeType::CurrentHealth 를 자신의 EAttributeType::CurrentAttack * 1 만큼 변경
	 * + 를 원할경우 TakeCureFromCursor, - 를 원할경우 TakeDamageFromCursor 사용
	 */
	FBattleAttributeModifier CreateBattleAttributeModifier(EAttributeType TargetAttributeType, EAttributeType BaseAttributeType, EModifierType ModifierType, float DamageRatio = 1.f);

	FBattleAttributeModifier GetDefaultAttackAttributeModifier();
	/*
	 * 모든 Current Attribute 값을 Base Attribute 값과 동기화
	 */
	void SetAllCurrentAttributeToBaseAttribute();
	
	void SetIsGuard(bool NewIsGuard);
	FText GetCharacterName();
	void SetCharacterName(const FText& NewCharacterName);
	bool IsDead();
	/*
	 * AbilityKey 를 기반으로 Ability 추가,
	 * AbilityKey 가 이미 추가되어 있는경우 추가하지 않고 false 반환
	 * 추가에 성공한 경우 true 반환
	 */
	bool GrantAbility(FName AbilityKey);
	
	TArray<ULshPF_Ability*> GetAbilityList();
	
	ILshPF_BattleInterface* GetOwnerBattleInterface();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FText CharacterName;
	
	/*
	 * Base* 해당 속성의 기본값, Buff, Debuff 로 인한 스텟 변화시 연상에 사용, 전투 중 불변
	 * Current* Buff, Debuff 등의 수치 변화가 적용된 값, 실제 연산에 사용, 전투 중 가변
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseMaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentMaxHealth;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseMana;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentMana;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseMaxMana;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentMaxMana;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseDefence;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentDefence;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseAbilityAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentAbilityAttack;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float BaseAbilityDefence;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	float CurrentAbilityDefence;

private:
	//사망 시 처리할 이벤트
	void OwnerDeadEvent();

	bool IsGuard = false;

	ILshPF_BattleInterface* CachedOwnerBattleInterface;
	UPROPERTY()
	TMap<FName, ULshPF_Ability*> AbilityMap;
};