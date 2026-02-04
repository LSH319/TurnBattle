// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LshPF_BattleComponent.h"

float ULshPF_BattleComponent::ApplyDamageToTarget(AActor* DamagedActor, AActor* DamageCauser, FDamageInfo DamageInfo)
{
	if (ULshPF_BattleComponent* TargetBattleComponent = DamagedActor->FindComponentByClass<ULshPF_BattleComponent>())
	{
		return TargetBattleComponent->TakeDamageFromCursor(DamageCauser, DamageInfo);
	}

	return -1;
}

float ULshPF_BattleComponent::TakeDamageFromCursor(AActor* DamageCauser, FDamageInfo DamageInfo)
{
	OnTakeDamageDelegate.Broadcast();
	
	CurrentHealth = CurrentHealth - DamageInfo.Damage;
	if (CurrentHealth <= 0)
	{
		//todo : 사망처리
	}
	return DamageInfo.Damage;
}
