// Fill F your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

  FVector HitLocation;  //out parameter //here because when in aimtowards crosshair, in  getlookvecotrhit in getsightrayhit, it didnt recognise hitlocation

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();



}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();           //aims every second


}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());          //method for use later. 

}



void  ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) { return; }        //if no tank, fail-

	
	if (GetSightRayHitLocation(HitLocation))                     //if there is a valid ray hit location
	{
	
		//tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);              //call aiming method


			     
	}

}



bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const    //function used to pretty much call everything. It is used for when aiming such as above
{
	//FInd the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//this is getting where the reticle is
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);         // since  x is 1/2 way and crosshair x is 0.5, and the y to be 1/3 up and crosshair y is 0.333

	//sets up the variable to be able to be used for when calling GetLookVectorHitLocation()
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))                 //if theres a valid look direction     
	{

		
		//line trace along that lookdirection and see what we hit(up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);


	}

	return true;

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const      //gets where player is aiming in X,Y,Z
{
	FVector CameraWorldLocation;  //to be discarded

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);


}

//line trace along that lookdirection and see what we hit(up to max range)
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const           //returns aiming location
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);          //start at start location and go out in the look direction to the range

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetPawn());

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		Params)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	
	HitLocation = FVector(0);
	return false; //line trace didnt succeed
	
}