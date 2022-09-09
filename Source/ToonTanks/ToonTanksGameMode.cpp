// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "PowerupBase.h"
#include "EPowerupType.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor) 
{
	if (DeadActor == Tank) 
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController) 
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
			ToonTanksPlayerController->bShowMouseCursor = true;
			ToonTanksPlayerController->CurrentMouseCursor = EMouseCursor::Default;
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;

		if (TargetTowers <= 0)
		{
			StartNewWave();
		}
	}
}

void AToonTanksGameMode::BeginPlay() 
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart() 
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	TargetTowers = GetTargetTowerCount();

	StartGame();

	if (ToonTanksPlayerController) 
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		ToonTanksPlayerController->CurrentMouseCursor = EMouseCursor::Crosshairs;

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController, 
			&AToonTanksPlayerController::SetPlayerEnabledState, 
			true
		);

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle, 
			PlayerEnableDelegate, 
			StartDelay, 
			false
		);
	}

	GetWorldTimerManager().SetTimer(
		PowerupSpawnTimerHandle,
		this,
		&AToonTanksGameMode::SpawnPowerup,
		PowerupSpawnRate,
		true,
		PowerupSpawnRate + StartDelay
	);
}

int32 AToonTanksGameMode::GetTargetTowerCount() 
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	
	return Towers.Num();
}

void AToonTanksGameMode::SpawnPowerup()
{
	float XSpawnPosition = FMath::RandRange(-PlaneXRange, PlaneXRange);
	float YSpawnPosition = FMath::RandRange(-PlaneYRange, PlaneYRange);

	// int32 PowerupTypeIndex = FMath::RandRange(0, PowerupList.Num());

	EPowerupType SelectedPowerupType = static_cast<EPowerupType>(rand() % 2);
	APowerupBase* Powerup = nullptr;

	switch (SelectedPowerupType)
	{
	case EPowerupType::HealthRestore:
		Powerup = GetWorld()->SpawnActor<APowerupBase>(HealthPowerupClass);
		break;
	case EPowerupType::ScatterShot:
		Powerup = GetWorld()->SpawnActor<APowerupBase>(ScatterShotPowerupClass);
		break;
	}
	
	Powerup->Init(XSpawnPosition, YSpawnPosition);
}

void AToonTanksGameMode::StartNewWave()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	TargetTowers = Towers.Num();

	for (AActor* Tower : Towers)
	{
		ATower* CastTower = Cast<ATower>(Tower);
		CastTower->ResetTowerForNewWave();
	}

	Tank->ResetHealth();

	NewWave(++WaveCounter);
}