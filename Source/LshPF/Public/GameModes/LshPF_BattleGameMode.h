// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LshPF_DataTableRow.h"
#include "GameModes/LshPF_GameModeBase.h"
#include "LshPF_BattleGameMode.generated.h"

class ALshPF_BattleCharacter_Base;
class UPlayerCharacterInfo;
class ULshPF_BattleComponent;
class ILshPF_BattleInterface;
class UEnemyMeshInfo;

DECLARE_DELEGATE_OneParam(FMontageEndedEvent, TArray<ILshPF_BattleInterface*>);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusUIReady);

USTRUCT(BlueprintType)
struct FTurnTableData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float RequireTime;
	
	ILshPF_BattleInterface* TargetCharacter;

	FTurnTableData() : RequireTime(0.f), TargetCharacter(nullptr) {}

	FTurnTableData(float _RequireTime, ILshPF_BattleInterface* TargetCharacter)
		: RequireTime(_RequireTime), TargetCharacter(TargetCharacter) {}

	bool IsEqualBattleInterface (const ILshPF_BattleInterface* Other)
	{
		return TargetCharacter == Other;
	}
};
/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_BattleGameMode : public ALshPF_GameModeBase
{
	GENERATED_BODY()

public:
	//~ Begin ACharacter Interface
	virtual void PostInitializeComponents() override;;
	virtual void BeginPlay() override;
	//~ End ACharacter Interface

	//캐릭터에서 begin play 시 호출될 함수
	void CharacterReady(ILshPF_BattleInterface* RequestBattleInterface);
	//캐릭터 사망 시 처리를 위해 호출 될 함수
	void CharacterDeath(ILshPF_BattleInterface* RemoveTarget);
	//Turn Table 에 삼입 요청을 위한 함수
	void RequestAddTurnTable(ILshPF_BattleInterface* RequestBattleInterface);
	//Turn 종료를 GM 에 알리기 위한 함수
	void TargetTurnEnd(ILshPF_BattleInterface* RequestBattleInterface);
	//Enemy 생성 시 DT 에서 Attribute 정보를 얻기 위한 함수
	FEnemyAttribute* GetEnemyAttributeByKeyName(FName EnemyKeyName) const;

	//Command 관련 Widget 준비여부 체크를 위한 함수, Status UI 와는 별도
	UFUNCTION(BlueprintCallable)
	void SetUIReady(bool NewIsUIReady);

	/*
	 * Status UI 준비 완료여부 확인을 위한 Delegate
	 * Status UI 가 UI Subsystem 에서 OnBattleComponentDelegate 에 대한 bind 완료 후 호출할것
	 */
	UPROPERTY(BlueprintCallable)
	FStatusUIReady StatusUIReady;

	FMontageEndedEvent TriggerMontageEndedEvent;
	FMontageEndedEvent ReactMontageEndedEvent;

	ILshPF_BattleInterface* GetRecentOwingTurnCharacter() const;
	
	/*
	 * Index로 List 에서 요소 반환
	 * 파라미터를 & 로받아 배열의 범위를 넘은값이 들어올 경우 범위 내부 값으로 조정
	 */
	ILshPF_BattleInterface* GetEnemyCharacterByIndex(int32& Index) const;
	ILshPF_BattleInterface* GetPlayerCharacterByIndex(int32& Index) const;
	
protected:
	void SortTurnTable();
	void SortEnemyList();
	bool IsGameReady() const;
	
	void GrantTurn();

	//todo : 테스트용, 삭제 후 game instance 값으로 사용할것
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 TestEnemyCount = 3;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TurnStartTP = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CharacterInterval = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FQuat EnemySpawnQuat = FQuat(0, 0, -180, 0);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FQuat PlayerSpawnQuat = FQuat(0, 0, 0, 0);
	
	UPROPERTY(EditDefaultsOnly, Category="SpawnPointActorTag")
	FName EnemySpawnPointActorTag = "EnemySpawnPoint";
	UPROPERTY(EditDefaultsOnly, Category="SpawnPointActorTag")
	FName PlayerSpawnPointActorTag = "PlayerSpawnPoint";
	
	UPROPERTY(EditDefaultsOnly, Category="EnemyInfo")
	UDataTable* EnemyAttributeData;
	UPROPERTY(EditDefaultsOnly, Category = "EnemyInfo")
	UEnemyMeshInfo* EnemyMeshInfo;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerInfo")
	UPlayerCharacterInfo* PlayerCharacterInfo;
	
	float GlobalTimer = 0.f;

	TArray<FTurnTableData> TurnTable;
	
	TArray<ILshPF_BattleInterface*> PlayerCharacterList;
	TArray<ILshPF_BattleInterface*> EnemyCharacterList;

private:
	//Turn 순서
	TQueue<ULshPF_BattleComponent*> WaitingRegisterComponents;
	//가장 최근 Turn을 시작한 캐릭터
	ILshPF_BattleInterface* RecentOwingTurnCharacter;
	bool IsStatusUIReady = false;
	bool IsTurnGranted = false;
	bool IsUIReady = false;

	/*
	 * Enemy Spawn 을 위한 함수
	 */
	void SpawnEnemies();

	void SpawnPlayerCharacters();
	
	//턴 캐릭터 행동 시 Trigger Montage 종료시 -> 타켓의 React -> 타켓의 React Montage 종료시 -> Turn End 흐
	//턴 캐릭터 행동 시 Trigger 가 되는 Montage 종료시 사용하기 위한 Callback
	//턴 캐릭터 행동 시 Trigger 가 되는 행동 : Attack, Skill, Item 사용
	void TriggerMontageEndedCallback(TArray<ILshPF_BattleInterface*> TargetBattleInterfaces);
	//턴 캐릭터의 Trigger 가 되는 Montage 에 대한 React Montage 종료시 사용하기 위한 Callback
	//턴 캐릭터의 Trigger 가 되는 Montage 에 대한 React : HitReact, Death
	void ReactMontageEndedCallback(TArray<ILshPF_BattleInterface*> TargetBattleInterfaces);
	
	UFUNCTION()
	void StatusUIReadyCallBack();
};
