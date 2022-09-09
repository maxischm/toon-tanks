// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUi.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UInGameUi : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealth(float HealthPercent);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UProgressBar* HealthBar = nullptr;

	virtual void NativeOnInitialized() override;

private:
};
