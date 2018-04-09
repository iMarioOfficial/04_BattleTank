// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;



	//no need to protect pointer as  added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));  //sets name for blueprint thing
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

void ATank::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f : Tank Fired!"), Time);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	
	TankAimingComponent->SetBarrelReference(BarrelToSet);


}

void ATank::SetTurretReference(UTurret* TurretToSet)
{

	TankAimingComponent->SetTurretReference(TurretToSet);


}
