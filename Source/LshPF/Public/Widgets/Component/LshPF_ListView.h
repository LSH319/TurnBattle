// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "Interface/LshPF_WidgetInterface.h"
#include "LshPF_ListView.generated.h"

/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_ListView : public UListView, public ILshPF_WidgetInterface
{
	GENERATED_BODY()

public:
	//~ Begin ILshPF_WidgetInterface Interface
	virtual void WidgetConfirmAction() override;
	virtual void WidgetBackAction() override;
	//~ End ILshPF_WidgetInterface Interface
};
