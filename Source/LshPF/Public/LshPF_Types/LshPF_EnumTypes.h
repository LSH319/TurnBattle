#pragma once

UENUM(BlueprintType)
enum class EConfirmScreenType : uint8
{
	Ok,
	YesNo,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EButtonType : uint8
{
	OkOrYes,
	No,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	KeyboardAndMouse,
	Gamepad,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	BaseHealth,
	CurrentHealth,
	BaseMaxHealth,
	CurrentMaxHealth,
	BaseMana,
	CurrentMana,
	BaseMaxMana,
	CurrentMaxMana,
	BaseSpeed,
	CurrentSpeed,
	BaseAttack,
	CurrentAttack,
	BaseDefence,
	CurrentDefence,
	BaseAbilityAttack,
	CurrentAbilityAttack,
	BaseAbilityDefence,
	CurrentAbilityDefence,
	Unknown UMETA(Hidden)
};