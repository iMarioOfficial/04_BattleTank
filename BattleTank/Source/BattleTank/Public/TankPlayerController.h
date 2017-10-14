// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"   //must be the last include


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
		ATank* GetControlledTank() const;

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override ;

		//start the tank moving the barrel so that the shot hits where the crosshair is
		void AimTowardsCrosshair();

		
	
private:
			//return an OUT parameter, tru if it hits landscape
		bool GetSightRayHitLocation(FVector& OutHitLocation) const;
};


