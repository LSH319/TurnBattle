// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/KeyTextureInfo.h"

TSoftObjectPtr<UTexture2D> UKeyTextureInfo::GetTextureByKey(const FKey& InKey)
{
	return KeyTextureMap.FindChecked(InKey);
}
