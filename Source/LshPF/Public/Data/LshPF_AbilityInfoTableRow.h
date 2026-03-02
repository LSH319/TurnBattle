#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LshPF_Types/LshPF_EnumTypes.h"
#include "LshPF_AbilityInfoTableRow.generated.h"

USTRUCT(BlueprintType)
struct FLshPF_AbilityInfoTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	FText AbilityName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EAttributeType DamageRatioAttributeType = EAttributeType::Unknown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	float DamageRatio = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EAttributeType TargetAttributeType = EAttributeType::Unknown;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EAttributeType CostAttributeType = EAttributeType::Unknown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	float AbilityCost = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	ETargetType TargetType = ETargetType::Unknown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category="AbilityInfo")
	EModifierType AbilityType = EModifierType::Unknown;
};
