// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerupBase.generated.h"

UCLASS()
class TOONTANKS_API APowerupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupBase();

	void Init(float XPosition, float YPosition);

protected:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PowerupMesh;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	USoundBase* CollectSound;

private:

	void Bounce();

	void Rotate();

	float StartHeight = 90.f;

	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
		float BouncingSpeed = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
		float BouncingDistance = 25.f;

	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
		float RotationSpeed = 30.f;

	bool bIsGoingDown = true;




public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
