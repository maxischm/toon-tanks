// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UFUNCTION(BLueprintImplementableEvent)
	void NewWave(int32 WaveNumber);

private:
	class ATank* Tank;

	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	UPROPERTY(EditDefaultsOnly, Category = "Powerup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APowerupBase> HealthPowerupClass;

	UPROPERTY(EditDefaultsOnly, Category = "Powerup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APowerupBase> ScatterShotPowerupClass;

	float PlaneXRange = 2450.f;
	float PlaneYRange = 2450.f;

	void SpawnPowerup();

	FTimerHandle PowerupSpawnTimerHandle;

	float PowerupSpawnRate = 10.f;

	void StartNewWave();

	int32 WaveCounter = 1;
};
