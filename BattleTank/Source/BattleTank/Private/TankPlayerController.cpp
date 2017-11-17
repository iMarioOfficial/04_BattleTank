// Fill F your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

  FVector HitLocation;  //out parameter //here because when in aimtowards crosshair, in  getlookvecotrhit in getsightrayhit, it didnt recognise hitlocation

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
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

	
	if (GetSightRayHitLocation(HitLocation))        //has a 'side-effect', is going to line trace
	{
	
		//tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);


			     
	}

}






bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//FInd the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);         // since  x is 1/2 way and crosshair x is 0.5, and the y to be 1/3 up and crosshair y is 0.333

	//De-project the sceen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{

		
		//line trace along that lookdirection and see what we hit(up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);


	}

	return true;

}



bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const
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
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);          //start at start location and go out in the look direction to the range

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetControlledTank());

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