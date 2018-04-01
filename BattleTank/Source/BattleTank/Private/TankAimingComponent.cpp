// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;  //TODO should this actually tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;

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

		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), Time)

	} else // if no solution	
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : No Aiming Solution Found"), Time)
	}	


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//get delta between barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //turn the forward direction of barrel into roll,pitch and yaw
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5.00);  //TODO remove magic number
}

