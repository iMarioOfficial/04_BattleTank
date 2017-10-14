// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing :%s"), *(ControlledTank->GetName()));
	}
	
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();


}




ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
	


}

void  ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;  //out parameter
	
	if (GetSightRayHitLocation(HitLocation))        //has a 'side-effect', is going to line trace
	{

		UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());

		
			//if hits landscape     //tell controlled tank to aim at this point
	}

}
	//get world location of linetrace through the crosshair, returns true if landscape is true
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;

}


