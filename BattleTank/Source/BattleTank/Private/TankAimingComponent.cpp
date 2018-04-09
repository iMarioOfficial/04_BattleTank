// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;

}

void UTankAimingComponent::SetTurretReference(UTurret * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	if (!Barrel) { return; }     //if there is no barrel then fail

	FVector OutLaunchVelocity;  //out parameter                        //setting up variables for SuggestProjectileVelocity()
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity					//Calculate the OutLaunchVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation, //out parameter
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace  //this parameter must be there to prevent bug
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //turns the launch velocity into a direction (green arrow to white one from the slides)
		MoveBarrelTowards(AimDirection);
	} 
	

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//get delta between barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //where I am aiming
	auto AimAsRotator = AimDirection.Rotation(); //Where I want to aim
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);  
	Turret->Rotate(DeltaRotator.Yaw);
	
}

