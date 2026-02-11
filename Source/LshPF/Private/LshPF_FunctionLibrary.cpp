// Fill out your copyright notice in the Description page of Project Settings.


#include "LshPF_FunctionLibrary.h"

#include "DeveloperSettings/LshPF_LevelSetting.h"
#include "DeveloperSettings/LshPF_WidgetMapSetting.h"

TSoftClassPtr<ULshPF_FocusableWidgetBase> ULshPF_FunctionLibrary::GetSoftFocusableWidgetBaseClassByTag(
	FGameplayTag InWidgetTag)
{
	const ULshPF_WidgetMapSetting* LshPFDeveloperSettings = GetDefault<ULshPF_WidgetMapSetting>();
	checkf(LshPFDeveloperSettings->LshPF_WidgetMap.Contains(InWidgetTag), TEXT("Could not find the corresponding widget under the tag %s"), *InWidgetTag.ToString());

	return LshPFDeveloperSettings->LshPF_WidgetMap.FindRef(InWidgetTag);
}

FString ULshPF_FunctionLibrary::GetSoftLevelPathByTag(FGameplayTag InTag)
{
	const ULshPF_LevelSetting* LshPFDeveloperSettings = GetDefault<ULshPF_LevelSetting>();
	checkf(LshPFDeveloperSettings->LshPF_LevelMap.Contains(InTag), TEXT("Could not find the corresponding level under the tag %s"), *InTag.ToString());
	
	return LshPFDeveloperSettings->LshPF_LevelMap.FindRef(InTag).ToSoftObjectPath().GetLongPackageName();
}
