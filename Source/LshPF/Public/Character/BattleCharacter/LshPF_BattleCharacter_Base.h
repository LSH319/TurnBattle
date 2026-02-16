// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/LshPF_CharacterBase.h"
#include "Interface/LshPF_BattleInterface.h"
#include "LshPF_BattleCharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnDelegate);

class ALshPF_BattleGameMode;
class ULshPF_BattleComponent;
/**
 * 
 */
UCLASS()
class LSHPF_API ALshPF_BattleCharacter_Base : public ALshPF_CharacterBase, public ILshPF_BattleInterface
{
	GENERATED_BODY()

public:
	ALshPF_BattleCharacter_Base();

	virtual ULshPF_BattleComponent* GetBattleComponent() const;
	
	//~ Begin ACharacter Interface
	/*
	 * override 하여 Attribute 초기화 후 Super 호출하기
	 * BaseHealth 와 BaseMana 를 Max 값으로 설정 후 Current 값을 Base 값과 동기화,
	 * 위 값들을 별도로 지정할 경우 Super 호출대신 코드 작성
	 */
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~ End ACharacter Interface

	//~ Begin LshPF_BattleInterface Interface
	UFUNCTION(BlueprintCallable)
	virtual int32 GetAttribute(EAttributeType AttributeType) override;
	UFUNCTION(BlueprintCallable)
	virtual void SetAttribute(EAttributeType AttributeType, int32 NewAttribute) override;
	virtual void TurnStart() override;
	UFUNCTION(BlueprintCallable)
	virtual void TurnEnd() override;
	virtual bool IsPlayerCharacter() override;
	virtual ULshPF_BattleComponent* GetBattleComponent() override;
	virtual void ToggleTargeting(bool IsActive) override;
	virtual void ToggleGuard(bool IsActive) override;
	virtual void PlayAnimMontageByTag(FGameplayTag AnimMontageTag) override;
	virtual int32 GetCharacterOrderPriority() const;
	//~ End LshPF_BattleInterface Interface

	UPROPERTY(BlueprintAssignable)
	FTurnDelegate OnTurnStartDelegate;
	UPROPERTY(BlueprintAssignable)
	FTurnDelegate OnTurnEndDelegate;

	void SetCharacterKey(FName NewCharacterKey);
	void SetCharacterName(const FText& NewCharacterName);

	void AddSoftAnimMontageMap(TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> MontageMap);

	void SetCharacterOrderPriority(int32 NewCharacterOrderPriority);

protected:
	ALshPF_BattleGameMode* GetBattleGameMode();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULshPF_BattleComponent* LshPF_BattleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystemComponent* TargetingParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystemComponent* GuardParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, UAnimMontage*> CharacterMontageMap;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CharacterKey = "001";

	int32 CharacterOrderPriority = 0;
	
	bool IsCharacterReady();
	
	bool IsMontageReady = false;
	bool IsBeginPlay = false;
	
private:
	UPROPERTY()
	ALshPF_BattleGameMode* CachedBattleGameMode;
};
