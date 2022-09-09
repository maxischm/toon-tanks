// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "ECannonType.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent = FindComponentByClass<UHealthComponent>();
}

void ABasePawn::HandleDestruction() 
{
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget) 
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(LookAtRotation);
}

void ABasePawn::Fire() 
{
	switch (CurrentCannonType)
	{
	case ECannonType::Default:
		DefaultFire();
		break;
	case ECannonType::ScatterShot:
		ScatterShotFire();
		break;
	}
}

void ABasePawn::DefaultFire()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation(),
		SpawnParams
		);
}

void ABasePawn::ScatterShotFire()
{
	float AngleOffset = -45.f;

	for (int32 i = 0; i < 5; ++i)
	{
		FRotator ProjectileRotation = ProjectileSpawnPoint->GetComponentRotation();
		ProjectileRotation.Add(0, AngleOffset, 0);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileRotation,
			SpawnParams
		);

		AngleOffset += 22.5f;
	}
}

void ABasePawn::ResetHealth()
{
	HealthComponent->ResetHealth();
}

void ABasePawn::ResetCannonType()
{
	ChangeCannonType(ECannonType::Default);
}

void ABasePawn::ChangeCannonType(ECannonType NewCannonType)
{
	CurrentCannonType = NewCannonType;

	// start timer for resetting cannon type
	GetWorldTimerManager().SetTimer(
		CannonTypeResetHandle,
		this,
		&ABasePawn::ResetCannonType,
		5.f,
		false
	);
}