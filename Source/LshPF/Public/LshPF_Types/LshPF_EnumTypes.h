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