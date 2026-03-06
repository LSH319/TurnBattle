// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_ListEntryBase.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_ListEntryBase : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	//~ Begin IUserObjectListEntry Interface
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	//~ End IUserObjectListEntry Interface
};
