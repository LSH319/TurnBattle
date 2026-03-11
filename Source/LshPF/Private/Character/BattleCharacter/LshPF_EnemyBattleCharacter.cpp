// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BattleCharacter/LshPF_EnemyBattleCharacter.h"

#include "LshPF_GameInstance.h"
#include "LshPF_GameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Component/LshPF_BattleComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/WidgetComponent.h"
#include "GameModes/LshPF_BattleGameMode.h"
#include "Subsystems/LshPF_UISubsystem.h"
#include "Widgets/LshPF_CharacterWidget.h"

ALshPF_EnemyBattleCharacter::ALshPF_EnemyBattleCharacter()
{
	BackCameraComponent->SetActive(false);
	FrontCameraComponent->SetActive(true);
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ALshPF_EnemyBattleCharacter::PostInitializeComponents()
{
	if(GetBattleGameMode())
	{
		if (const FEnemyAttribute* EnemyAttribute = GetBattleGameMode()->GetEnemyAttributeByKeyName(CharacterKey))
		{
			LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxHealth, EnemyAttribute->BaseMaxHealth);
			LshPF_BattleComponent->SetAttribute(EAttributeType::BaseMaxMana, EnemyAttribute->BaseMaxMana);
			LshPF_BattleComponent->SetAttribute(EAttributeType::BaseSpeed, EnemyAttribute->BaseSpeed);
			LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAttack, EnemyAttribute->BaseAttack);
			LshPF_BattleComponent->SetAttribute(EAttributeType::BaseDefence, EnemyAttribute->BaseDefence);
			LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityAttack, EnemyAttribute->BaseAbilityAttack);
			LshPF_BattleComponent->SetAttribute(EAttributeType::BaseAbilityDefence, EnemyAttribute->BaseAbilityDefence);
		}
	}

	HealthBar->SetVisibility(false);
	
	Super::PostInitializeComponents();
}

void ALshPF_EnemyBattleCharacter::TurnStart()
{
	Super::TurnStart();

	if (ULshPF_UISubsystem* UISubsystem = ULshPF_UISubsystem::Get(GetWorld()))
	{
		UISubsystem->SetWidgetSwitcherVisibilityWithTag(LshPF_GameplayTags::LshPF_WidgetStack_GameHud, ESlateVisibility::Hidden);
	}
	SetViewTargetSelf(true);
	TargetList.Empty();
}

void ALshPF_EnemyBattleCharacter::CharacterDeath()
{
	HealthBar->SetVisibility(false);
	HealthBar->RemoveFromRoot();
	
	Super::CharacterDeath();
}

void ALshPF_EnemyBattleCharacter::ToggleTargeting(bool IsActive)
{
	Super::ToggleTargeting(IsActive);

	if (IsActive)
	{
		HealthBar->SetVisibility(true);
	}
	else
	{
		HealthBar->SetVisibility(false);
	}
}

void ALshPF_EnemyBattleCharacter::SetRandomTargetInTargetList()
{
	TargetList.Empty();
	
	ULshPF_GameInstance* GameInstance = Cast<ULshPF_GameInstance>(GetGameInstance());
	int TargetIndex = FMath::RandRange(0, GameInstance->GetPlayerCharacterKeyNames().Num() - 1);
	
	TargetList.Add(GetBattleGameMode()->GetPlayerCharacterByIndex(TargetIndex));
}

void ALshPF_EnemyBattleCharacter::Action_Attack()
{
	if (TargetList.IsEmpty())
	{
		SetRandomTargetInTargetList();
	}
	PlayAnimMontageByTag(LshPF_GameplayTags::LshPF_AnimMontage_Attack);
}

void ALshPF_EnemyBattleCharacter::Action_Guard()
{
	ToggleGuard(true);
}

TArray<ILshPF_BattleInterface*> ALshPF_EnemyBattleCharacter::GetTargetInterfaceList()
{
	return TargetList;
}

FBattleAttributeModifier ALshPF_EnemyBattleCharacter::GetTargetModifier()
{
	return LshPF_BattleComponent->GetDefaultAttackAttributeModifier();
}

void ALshPF_EnemyBattleCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ULshPF_CharacterWidget* CastHealthBar = Cast<ULshPF_CharacterWidget>(HealthBar->GetUserWidgetObject()))
	{
		CastHealthBar->SetOwnerBattleComponent(LshPF_BattleComponent);
	}
}
