// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "LshPF_BattleComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamageDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangedDelegate, EAttributeType, float);

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

	FDamageInfo(){}
	
	FDamageInfo(float InDamage, bool InIsCritical)
	{
		Damage = InDamage;
		IsCritical = InIsCritical;
	}
	
	UPROPERTY()
	float Damage = 0;
	
	UPROPERTY()
	bool IsCritical = false;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LSHPF_API ULshPF_BattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//todo : Damage 관련 계산 수정 필요, 기반 스텟, 배율 등
	static FDamageInfo CreateDamageInfo(float InDamage, bool InIsCritical);
	
	/*
	* Target 에게 Damage 적용
	* DamagedActorBattleComponent Damage를 받는 Actor BattleComponent
	* DamageCauserBattleComponent Damage를 가하는 Actor BattleComponent
	* DamageInfo Damage 관련 정보
	* return : 실제 Target 에 적용된 Damage
	 */
	UFUNCTION(BlueprintCallable)
	float ApplyDamageToTarget(ULshPF_BattleComponent* DamagedActorBattleComponent, ULshPF_BattleComponent* DamageCauserBattleComponent, FDamageInfo DamageInfo);

	/*
	 * Damage 받을경우 처리
	 * DamageCauserBattleComponent Damage를 가하는 Actor BattleComponent
	 * DamageInfo Damage 관련 정보
	 * return : 실제 적용된 Damage
	 */
	UFUNCTION(BlueprintCallable)
	float TakeDamageFromCursor(ULshPF_BattleComponent* DamageCauserBattleComponent, FDamageInfo DamageInfo);

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

	/*
	 * 모든 Current Attribute 값을 Base Attribute 값과 동기화
	 */
	void SetAllCurrentAttributeToBaseAttribute();

	FText GetCharacterName();
	
	FOnAttributeChangedDelegate AttributeChangedDelegate;
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
};
