// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AbilityEffectInfo.h"

TSoftObjectPtr<UParticleSystem> UAbilityEffectInfo::GetParticleByKeyName(FName AbilityKey)
{
	return AbilityParticleMap.FindChecked(AbilityKey);
}
