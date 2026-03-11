// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "UObject/Interface.h"
#include "LshPF_BattleInterface.generated.h"

class ULshPF_BattleComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULshPF_BattleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LSHPF_API ILshPF_BattleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetAttribute(EAttributeType AttributeType) = 0; 
	virtual void SetAttribute(EAttributeType AttributeType, int32 NewAttribute) = 0;
	virtual void TurnStart() = 0;
	virtual void TurnEnd() = 0;
	virtual bool IsPlayerCharacter() = 0;
	virtual ULshPF_BattleComponent* GetBattleComponent() = 0;
	virtual void ToggleTargeting(bool IsActive) = 0;
	virtual void ToggleGuard(bool IsActive) = 0;
	virtual void PlayAnimMontageByTag(FGameplayTag AnimMontageTag) = 0;
	virtual int32 GetCharacterOrderPriority() const = 0;
	virtual FVector GetBattleCharacterLocation() = 0;
	virtual void SetLookAtRotation(FVector TargetLocation) = 0;
	virtual void CharacterDeath() = 0;
	virtual void SetViewTargetSelf(bool TargetIsFrontCamera) = 0;
	virtual void ShowApplyValue(int ApplyValue, bool IsDamage) = 0;
};
