#pragma once

#include "CoreMinimal.h"
#include "EPowerupType.generated.h"

UENUM(BlueprintType)
enum class EPowerupType : uint8
{
	HealthRestore = 0,
	ScatterShot,
};