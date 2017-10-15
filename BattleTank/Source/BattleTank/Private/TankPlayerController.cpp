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

		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());

		
			//if hits landscape     //tell controlled tank to aim at this point
	}

}
	//get world location of linetrace through the crosshair, returns true if landscape is true
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//FInd the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);         // since  x is 1/2 way and crosshair x is 0.5, and the y to be 1/3 up and crosshair y is 0.333

	//De-project the sceen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Looking at %s"), *LookDirection.ToString())
	}



	//line trace along that look direction and see what we hit
	return true;

}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const
{
	FVector CameraWorldLocation;  //to be discarded

		return DeprojectScreenPositionToWorld(
			ScreenLocation.X,
			ScreenLocation.Y,
			CameraWorldLocation,
			LookDirection);

	
	

}