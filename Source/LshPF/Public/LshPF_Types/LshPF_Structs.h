#pragma once
#include "LshPF_EnumTypes.h"
#include "LshPF_Structs.generated.h"

USTRUCT(BlueprintType)
struct FBattleAttributeModifier
{
	GENERATED_BODY()

	FBattleAttributeModifier()
	:TargetAttribute(EAttributeType::Unknown), ModifierType(EModifierType::Damage_Default)
	{}
	
	FBattleAttributeModifier(float InModifyValue, EAttributeType InAttributeType, EModifierType InModifierType)
	:ModifyValue(InModifyValue), IsCritical(false), TargetAttribute(InAttributeType), ModifierType(InModifierType)
	{
	}

	//변경할 값
	UPROPERTY()
	float ModifyValue = 0;

	//크리티컬 여부
	UPROPERTY()
	bool IsCritical = false;

	//변경할 Attribute
	UPROPERTY()
	EAttributeType TargetAttribute;
	
	UPROPERTY()
	EModifierType ModifierType;
};