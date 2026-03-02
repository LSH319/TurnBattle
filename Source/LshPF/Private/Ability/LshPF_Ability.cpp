// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/LshPF_Ability.h"

#include "Component/LshPF_BattleComponent.h"
#include "Controllers/LshPF_PlayerController_Battle.h"
#include "GameModes/LshPF_BattleGameMode.h"
#include "Interface/LshPF_BattleInterface.h"
#include "Kismet/GameplayStatics.h"

void ULshPF_Ability::SetOwnerBattleComponent(ULshPF_BattleComponent* OwnerBattleComponentPointer)
{
	OwnerBattleComponent = OwnerBattleComponentPointer;
}

void ULshPF_Ability::InitAbilityData(FName AbilityKey)
{
	//todo : DT 를 통해 Data 초기화
	//DT 에서 AbilityKey 를 통해 값을 가져온 뒤 사용
	/*AbilityName;
	DamageRatioAttributeType = EAttributeType::Unknown;
	DamageRatio = 0.f;
	TargetAttributeType
	CostAttributeType = EAttributeType::Unknown;
	AbilityCost = 0.f;
	TargetType = ETargetType::Unknown;
	AbilityType*/
}

bool ULshPF_Ability::IsCanActivate()
{
	if (OwnerBattleComponent.IsValid())
	{
		if (OwnerBattleComponent->GetAttribute(CostAttributeType) >= AbilityCost)
		{
			//Attribute 가 Cost 보다 높은경우, True
			return true;
		}
	}
	
	return false;
}

void ULshPF_Ability::CommitAbility()
{
	if (IsCanActivate())
	{//IsCanActivate 에서 true 인 경우는 OwnerBattleComponent 의 Valid 체크도 통과한 경우
		//Attribute 를 Cost 만큼 감소
		OwnerBattleComponent->SetAttribute(CostAttributeType, OwnerBattleComponent->GetAttribute(CostAttributeType) - AbilityCost);
		ActivateAbility();
	}
}

void ULshPF_Ability::ActivateAbility()
{
	//todo : 사용시 로직 구현
	TArray<ULshPF_BattleComponent*> TargetBattleComponents = GetTargetBattleComponents();
	FBattleAttributeModifier AttributeModifier = OwnerBattleComponent->CreateBattleAttributeModifier(TargetAttributeType, DamageRatioAttributeType, AbilityType, DamageRatio);

	for (ULshPF_BattleComponent* TargetBattleComponent : TargetBattleComponents)
	{
		//GetBattleGameMode()->TriggerMontageEndedEvent.ExecuteIfBound(TargetBattleComponents);
		//OwnerBattleComponent->ApplyModifierToTarget(TargetBattleComponent, OwnerBattleComponent.Get(), AttributeModifier);
		//UGameplayStatics::SpawnEmitterAttached()
    	//UGameplayStatics::SpawnEmitterAttached()
	}
	
}

TArray<ULshPF_BattleComponent*> ULshPF_Ability::GetTargetBattleComponents()
{
	TArray<ULshPF_BattleComponent*> TargetBattleComponents;
	switch (TargetType)
	{
	case ETargetType::EnemySingle:
	case ETargetType::PlayerSingle:
		TargetBattleComponents.Add(GetBattlePlayerController()->GetTargetBattleComponent());
		break;
	case ETargetType::EnemyAll:
		for (ILshPF_BattleInterface* TargetBattleInterface : GetBattleGameMode()->GetEnemyCharacters())
		{
			TargetBattleComponents.Add(TargetBattleInterface->GetBattleComponent());
		}
		break;
	case ETargetType::PlayerAll:
		for (ILshPF_BattleInterface* TargetBattleInterface : GetBattleGameMode()->GetPlayerCharacters())
		{
			TargetBattleComponents.Add(TargetBattleInterface->GetBattleComponent());
		}
		break;
	case ETargetType::Unknown:
		break;
	}
	return TargetBattleComponents;
}

ALshPF_BattleGameMode* ULshPF_Ability::GetBattleGameMode()
{
	if (!CachedBattleGameMode.IsValid())
	{
		CachedBattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	}
	return CachedBattleGameMode.Get();
}

ALshPF_PlayerController_Battle* ULshPF_Ability::GetBattlePlayerController()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<ALshPF_PlayerController_Battle>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
	return CachedPlayerController.Get();
}
