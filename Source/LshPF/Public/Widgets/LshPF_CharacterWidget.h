// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LshPF_CharacterWidget.generated.h"

class ULshPF_BattleComponent;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_CharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerBattleComponent(ULshPF_BattleComponent* OwnerBattleComponent);
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnSetOwnerBattleComponent(ULshPF_BattleComponent* OwnerBattleComponent);

private:
	UPROPERTY()
	TWeakObjectPtr<ULshPF_BattleComponent> CachedOwnerBattleComponent;
};
