// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BattleCharacter/LshPF_BattleCharacter_Base.h"

#include "Component/LshPF_BattleComponent.h"
#include "GameModes/LshPF_BattleGameMode.h"

ALshPF_BattleCharacter_Base::ALshPF_BattleCharacter_Base()
{
	LshPF_BattleComponent = CreateDefaultSubobject<ULshPF_BattleComponent>("BattleComponent");
}

ULshPF_BattleComponent* ALshPF_BattleCharacter_Base::GetBattleComponent() const
{
	return LshPF_BattleComponent;
}

void ALshPF_BattleCharacter_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//BaseHealth 와 BaseMana 를 Max 값으로 설정
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseHealth,LshPF_BattleComponent->GetAttribute(EAttributeType::BaseMaxHealth));
	LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMana,LshPF_BattleComponent->GetAttribute(EAttributeType::BaseMana));

	//Current 값을 Base 값과 동기화
	LshPF_BattleComponent->SetAllCurrentAttributeToBaseAttribute();
}

void ALshPF_BattleCharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	GetBattleGameMode()->RequestAddTurnTable(this);
}

int32 ALshPF_BattleCharacter_Base::GetAttribute(EAttributeType AttributeType)
{
	return LshPF_BattleComponent->GetAttribute(AttributeType);
}

void ALshPF_BattleCharacter_Base::SetAttribute(EAttributeType AttributeType, int32 NewAttribute)
{
	LshPF_BattleComponent->SetAttribute(AttributeType, NewAttribute);
}

void ALshPF_BattleCharacter_Base::TurnStart()
{
	
}

void ALshPF_BattleCharacter_Base::TurnEnd()
{
	GetBattleGameMode()->TargetTurnEnd(this);
}

ALshPF_BattleGameMode* ALshPF_BattleCharacter_Base::GetBattleGameMode()
{
	if (!CachedBattleGameMode)
	{
		CachedBattleGameMode = Cast<ALshPF_BattleGameMode>(GetWorld()->GetAuthGameMode());
	}
	return CachedBattleGameMode;
}
