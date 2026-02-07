// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LshPF_CharacterBase.h"
#include "Interface/LshPF_BattleInterface.h"
#include "LshPF_BattleCharacter.generated.h"

class ULshPF_BattleComponent;
/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_BattleCharacter : public ALshPF_CharacterBase, public ILshPF_BattleInterface
{
	GENERATED_BODY()

public:
	ALshPF_BattleCharacter();

	virtual ULshPF_BattleComponent* GetBattleComponent() const;
	
	//~ Begin ACharacter Interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~ End ACharacter Interface

	//~ Begin ACharacter Interface
	UFUNCTION(BlueprintCallable)
	virtual int32 GetAttribute(EAttributeType AttributeType) override;
	UFUNCTION(BlueprintCallable)
	virtual void SetAttribute(EAttributeType AttributeType, int32 NewAttribute) override;
	virtual void TurnStart() override;
	virtual void TurnEnd() override;
	//~ End ACharacter Interface
	
protected:
	UPROPERTY(EditAnywhere)
	ULshPF_BattleComponent* LshPF_BattleComponent;
};
