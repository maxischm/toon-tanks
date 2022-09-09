// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupHealthRestore.h"
#include "Components/PrimitiveComponent.h"
#include "Tank.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

void APowerupHealthRestore::BeginPlay()
{
	Super::BeginPlay();

	PowerupMesh->OnComponentBeginOverlap.AddDynamic(this, &APowerupHealthRestore::OnOverlapBegin);
}

void APowerupHealthRestore::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATank* Tank = Cast<ATank>(OtherActor))
	{
		// Overlapped with Tank => Add Health to the tank
		Tank->RestoreHealth(RestoredHealthAmount);

		if (CollectSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());
		}

		Destroy();
	}
}