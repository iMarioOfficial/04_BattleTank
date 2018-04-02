// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"   //header for Barrel
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"   //header for suggestprojectilevel
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward Declaration
class UTankBarrel; 
class UTurret;

//Holds barrel properties 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	void SetTurretReference(UTurret* TurretToSet);



protected:

private:	
	
	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

		
	
};
