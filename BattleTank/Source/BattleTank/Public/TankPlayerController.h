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
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;
private:
		

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override ;

		//start the tank moving the barrel so that the shot hits where the crosshair is
		void AimTowardsCrosshair();

			//return an OUT parameter, tru if it hits landscape
		bool GetSightRayHitLocation(FVector& HitLocation) const;
		
			UPROPERTY(EditDefaultsOnly)
				float CrossHairXLocation = 0.5;
			UPROPERTY(EditDefaultsOnly)
				float CrossHairYLocation = 0.33333;
	

			bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const;

			bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const;

			UPROPERTY(EditDefaultsOnly)
				float LineTraceRange = 10000000000;  //100,000 km( is in cm)

};


