// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/KeyTextureInfo.h"

UTexture2D* UKeyTextureInfo::GetTextureByKey(FKey InKey)
{
	return KeyTextureMap.FindChecked(InKey);
}
