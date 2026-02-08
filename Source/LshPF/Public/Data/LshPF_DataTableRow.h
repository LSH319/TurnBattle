#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LshPF_DataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FEnemyAttribute : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	int32 BaseMaxHealth = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	int32 BaseMaxMana = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	int32 BaseSpeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	int32 BaseAttack = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	int32 BaseDefence = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	int32 BaseAbilityAttack = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attribute")
	int32 BaseAbilityDefence = 0;
};
