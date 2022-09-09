// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUi.h"
#include "Components/ProgressBar.h"

void UInGameUi::SetHealth(float HealthPercent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(HealthPercent);
	}
}

void UInGameUi::NativeOnInitialized()
{
	if (HealthBar)
	{
		HealthBar->SetPercent(1.f);
	}
}