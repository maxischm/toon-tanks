// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupScatterShot.h"
#include "Components/PrimitiveComponent.h"
#include "Tank.h"
#include "ECannonType.h"
#include "Kismet/GameplayStatics.h"

void APowerupScatterShot::BeginPlay()
{
	Super::BeginPlay();

	PowerupMesh->OnComponentBeginOverlap.AddDynamic(this, &APowerupScatterShot::OnOverlapBegin);
}

void APowerupScatterShot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATank* Tank = Cast<ATank>(OtherActor))
	{
		// Overlapped with Tank => Add Health to the tank
		Tank->ChangeCannonType(ECannonType::ScatterShot);

		if (CollectSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());
		}

		Destroy();
	}
}