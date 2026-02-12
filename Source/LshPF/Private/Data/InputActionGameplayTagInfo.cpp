// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputActionGameplayTagInfo.h"

UInputAction* UInputActionGameplayTagInfo::GetInputActionByGameplayTag(const FGameplayTag InFGameplayTag)
{
	return InputActionGameplayTagMap.FindChecked(InFGameplayTag);
}
