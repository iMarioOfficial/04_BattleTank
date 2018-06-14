// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	//so that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime) //if we are reloading
	{
		FiringState = EFiringState::Reloading;
	}
	else if (isBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTurret* TurretToSet)
{
	//no need to protect since if toset is null it will jsut set as nullptr, which it already is
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel)) { return; }     //if there is no barrel then fail

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
		 AimDirection = OutLaunchVelocity.GetSafeNormal(); //turns the launch velocity into a direction (green arrow to white one from the slides)
		MoveBarrelTowards(AimDirection);
	} 
	

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	if (!ensure(Barrel) && !ensure(Turret)) { return; }

	//get delta between barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //where I am aiming
	auto AimAsRotator = AimDirection.Rotation(); //Where I want to aim
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);  
	
	//Rotate the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180) //absolute value 
	{
	Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
	
}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector(); //where I am aiming
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire()
{


	if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked)
	{
		if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) { return; }
		//spawn projectile at socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileSocket")),
			Barrel->GetSocketRotation(FName("ProjectileSocket"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		RoundsLeft--;

		LastFireTime = FPlatformTime::Seconds();
	}

}


