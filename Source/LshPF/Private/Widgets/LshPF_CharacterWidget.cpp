// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/LshPF_CharacterWidget.h"

#include "Component/LshPF_BattleComponent.h"

void ULshPF_CharacterWidget::SetOwnerBattleComponent(ULshPF_BattleComponent* OwnerBattleComponent)
{
	OnSetOwnerBattleComponent(OwnerBattleComponent);
	CachedOwnerBattleComponent = OwnerBattleComponent;
}
