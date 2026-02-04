// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

	UPROPERTY(BlueprintAssignable)
	FOnTakeDamageDelegate OnTakeDamageDelegate;
	
protected:
	/*
	 * Base* 해당 속성의 기본값, Buff, Debuff 로 인한 스텟 변화시 연상에 사용, 전투 중 불변
	 * Current* Buff, Debuff 등의 수치 변화가 적용된 값, 실제 연산에 사용, 전투 중 가변
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 BaseHealth;
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	int32 MaxBaseHealth;
	UPROPERTY(BlueprintReadWrite)
	int32 MaxCurrentHealth;
};
