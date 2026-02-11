#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LshPF_DataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FEnemyAttribute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	float BaseMaxHealth = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	float BaseMaxMana = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	float BaseSpeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	float BaseAttack = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	float BaseDefence = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	float BaseAbilityAttack = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	float BaseAbilityDefence = 0;
};
