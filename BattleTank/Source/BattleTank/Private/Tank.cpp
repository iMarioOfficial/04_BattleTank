// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"


void ATank::BeginPlay()
{
	Super::BeginPlay(); //Needed for BP BeginPlay to work
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY C++ Play Begun!"), *TankName)

}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY  C++ Constructed!"), *TankName)


}



void ATank::AimAt(FVector HitLocation) {              //this is here to have both AI and player use the same aiming component
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);     //delegates the aiming to AimingComponent calss
}



void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (Barrel && isReloaded)
	{
	

		//spawn projectile at socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileSocket")),
			Barrel->GetSocketRotation(FName("ProjectileSocket"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

	}
	
}