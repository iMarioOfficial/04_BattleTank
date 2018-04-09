// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "TankBarrel.h"

void UTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Yaw = RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0, Yaw, 0));
}


