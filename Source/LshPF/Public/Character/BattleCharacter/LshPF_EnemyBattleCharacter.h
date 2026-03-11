// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"
#include "LshPF_EnemyBattleCharacter.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_EnemyBattleCharacter : public ALshPF_BattleCharacter_Base
{
	GENERATED_BODY()

public:
	ALshPF_EnemyBattleCharacter();
	
	//~ Begin ACharacter Interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~ End ACharacter Interface

	//~ Begin LshPF_BattleInterface Interface
	virtual void TurnStart() override;
	virtual void CharacterDeath() override;
	//~ End LshPF_BattleInterface Interface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	/*
	 * TargetList 를 초기화 후, 무작위 PlayerCharacter 를 선택해 TargetList 에 삽입
	 */
	UFUNCTION(BlueprintCallable)
	void SetRandomTargetInTargetList();
	/*
	 * TargetList 에게 공격 실행, TargetList 를 설정하지 않은 경우 무작위 PlayerCharacter 에게 공격
	 * 호출 시 AnimMontage 실행 후 턴 종료까지 자동 실행
	 */
	UFUNCTION(BlueprintCallable)
	void Action_Attack();
	/*
	 * Guard 실행, 실행 후 턴 종료
	 */
	UFUNCTION(BlueprintCallable)
	void Action_Guard();
	
	//~ Begin ALshPF_BattleCharacter_Base Interface
	virtual TArray<ILshPF_BattleInterface*> GetTargetInterfaceList() override;
	virtual FBattleAttributeModifier GetTargetModifier() override;
	//~ End ALshPF_BattleCharacter_Base Interface
	
private:
	TArray<ILshPF_BattleInterface*> TargetList;
};
