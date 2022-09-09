// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction() {
	Super::HandleDestruction();

	GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ATower::BeginPlay() {
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	StartFiringAutomation();
}

void ATower::CheckFireCondition() 
{
	if (InFireRange() && Tank && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::InFireRange() {
	if (Tank) 
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= FireRange) 
		{
			return true;
		}
	}
	return false;
}

void ATower::StartFiringAutomation()
{
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireDelay,
		true
	);
}

void ATower::ResetTowerForNewWave()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	ResetHealth();
	DecreaseFireDelay();

	StartFiringAutomation();
}