// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//no need to protect pointer as  added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));  //adds aiming component to the tank blueprint
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);          

}


void ATank::AimAt(FVector HitLocation) {              //this is here to have both AI and player use the same aiming component

	
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);     //delegates the aiming to AimingComponent calss


}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;


}

void ATank::SetTurretReference(UTurret* TurretToSet)
{

	TankAimingComponent->SetTurretReference(TurretToSet);


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