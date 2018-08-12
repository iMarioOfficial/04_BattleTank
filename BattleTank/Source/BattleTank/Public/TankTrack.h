// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h" //for getWorld
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set max driving force and to apply forces to the track
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
	 UTankTrack();


	 TArray<class ASprungWheel*> GetWheels() const;
	
	 void DriveTrack(float CurrentThrottle);



public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);


	
	//Max force in newtons
	UPROPERTY(EditDefaultsonly)
		float TrackMaxDrivingForce = 40000000.0; //Attume 40 Ton Tank at 1g Acceleration
	

};
