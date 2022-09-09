// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerupBase::APowerupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Powerup Mesh"));
	RootComponent = PowerupMesh;
}

void APowerupBase::Init(float XPosition, float YPosition)
{
	FVector SpawnPosition(XPosition, YPosition, StartHeight);
	SetActorLocation(SpawnPosition, true);
}

// Called every frame
void APowerupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Bounce();
	Rotate();
}

void APowerupBase::Bounce()
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.Z = (bIsGoingDown ? -1 : 1) * UGameplayStatics::GetWorldDeltaSeconds(this) * BouncingSpeed;
	AddActorLocalOffset(DeltaLocation, true);

	// Check if min/max height of bounce was reached
	if (bIsGoingDown && StartHeight - BouncingDistance > GetActorLocation().Z
		|| !bIsGoingDown && StartHeight + BouncingDistance < GetActorLocation().Z)
	{
		bIsGoingDown = !bIsGoingDown;
	}
}

void APowerupBase::Rotate()
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = UGameplayStatics::GetWorldDeltaSeconds(this) * RotationSpeed;
	AddActorLocalRotation(DeltaRotation, true);
}