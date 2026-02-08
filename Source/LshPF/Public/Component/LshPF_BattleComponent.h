// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "LshPF_BattleComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTakeDamageDelegate);

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
	/*
	* Target 에게 Damage 적용
	* DamagedActor Damage를 받는 Actor
	* DamageCauser Damage를 가하는 Actor 
	* DamageInfo Damage 관련 정보
	* return : 실제 Target 에 적용된 Damage
	 */
	UFUNCTION(BlueprintCallable)
	float ApplyDamageToTarget(AActor* DamagedActor, AActor* DamageCauser, FDamageInfo DamageInfo);

	/*
	 * Damage 받을경우 처리
	 * DamageCauser Damage를 가하는 Actor 
	 * DamageInfo Damage 관련 정보
	 * return : 실제 적용된 Damage
	 */
	UFUNCTION(BlueprintCallable)
	float TakeDamageFromCursor(AActor* DamageCauser, FDamageInfo DamageInfo);

	/*
	 * EAttributeType 에 따른 Attribute 값 반환
	 * AttributeType 원하는 Attribute 값
	 * return : EAttributeType 에 따른 Attribute 값
	 */
	UFUNCTION(BlueprintCallable)
	int32 GetAttribute(EAttributeType AttributeType); 

	/*
	 * EAttributeType 에 따른 Attribute 값을 NewAttribute 값으로 설정
	 * AttributeType 원하는 Attribute 값
	 * NewAttribute 변경하길 원하는 값
	 */
	UFUNCTION(BlueprintCallable)
	void SetAttribute(EAttributeType AttributeType, int32 NewAttribute);
	
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamageDelegate OnTakeDamageDelegate;

	/*
	 * 모든 Current Attribute 값을 Base Attribute 값과 동기화
	 */
	void SetAllCurrentAttributeToBaseAttribute();
protected:
	/*
	 * Base* 해당 속성의 기본값, Buff, Debuff 로 인한 스텟 변화시 연상에 사용, 전투 중 불변
	 * Current* Buff, Debuff 등의 수치 변화가 적용된 값, 실제 연산에 사용, 전투 중 가변
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseMaxHealth;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentMaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseMana;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseMaxMana;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentMaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseSpeed;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseAttack;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseDefence;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentDefence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseAbilityAttack;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentAbilityAttack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseAbilityDefence;
	UPROPERTY(BlueprintReadWrite, Category = "Attribute")
	int32 CurrentAbilityDefence;
};
