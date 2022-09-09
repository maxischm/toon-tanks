// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	void DecreaseFireDelay() { FireDelay -= 0.2f; }

	void StartFiringAutomation();

	void ResetTowerForNewWave();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 100;

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireDelay = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float StartFireDelay = 2.f;

	void CheckFireCondition();

	bool InFireRange();
};
