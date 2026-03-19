// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Component/FocusableComponent/LshPF_FocusableWidgetBase.h"
#include "LshPF_CharacterCheckList.generated.h"

class UImage;
struct FPlayerBattleCharacterInfo;
class ULshPF_FocusableCheckBox;
class UDynamicEntryBox;
/**
 * 
 */
UCLASS()
class LSHPF_API ULshPF_CharacterCheckList : public ULshPF_FocusableWidgetBase
{
	GENERATED_BODY()
	
public:
	//~ Begin UUserWidget Interface
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	//~ End UUserWidget Interface
	
	//~ Begin ULshPF_FocusableWidgetBase Interface
	virtual void WidgetConfirmAction() override;
	virtual void WidgetBackAction() override;
	//~ End ULshPF_FocusableWidgetBase Interface

	/*
	 * 위젯에서 체크할 캐릭터 데이터 설정
	 */
	void SetTargetCharacter(FName CharacterKey, FPlayerBattleCharacterInfo CharacterInfo);
	/*
	 * 캐릭터의 사용 여부 설정
	 */
	void SetIsCharacterUse(bool InIsCharacterUse);
	
	UFUNCTION(BlueprintCallable)
	ULshPF_FocusableCheckBox* GetIsCharacterUse() const;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor OnFocusBackgroundColor;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor DefaultBackgroundColor;

	/*
	 * 위젯에서 관리하는 캐릭터 데이터 취합하여 Return
	 * Return key : 관리한는 캐릭터 Key, value : 해당 캐릭터가 사용할 Ability Key 배열
	 */
	TTuple<FName, TArray<FName>> GetTargetCharacterInfo();
	/*
	 * 캐릭터 사용여부 체크
	 */
	bool IsTargetCharacterUse() const;

protected:
	virtual void NativeConstruct() override;

	/*
	 * Instance 데이터에서 AbilityKey 를 통한 Ability 를 캐릭터가 사용하는지 여부
	 * return Instance 데이터에서 관리하는 캐릭터 Ability 배열에 InAbilityKey 가 있을경우 true
	 */
	bool AbilityIsUseInInstance(FName InAbilityKey);
	
	UPROPERTY(EditDefaultsOnly, Category="AbilityInfo")
	UDataTable* AbilityData;
private:
	FName TargetCharacterKey;
	
	//***** Bound Widgets ***** //
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundImage;
	
	UPROPERTY(meta = (BindWidget))
	ULshPF_FocusableCheckBox* IsCharacterUse;
		
	UPROPERTY(meta = (BindWidget))
	UDynamicEntryBox* DynamicEntryBox_SkillSetting;
	//***** Bound Widgets ***** //
};
