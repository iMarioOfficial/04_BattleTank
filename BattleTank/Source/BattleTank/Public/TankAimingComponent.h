// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"   //header for Barrel
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"   //header for suggestprojectilevel
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming, 
	Locked
};

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


	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTurret* TurretToSet);


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
		
private:	
	
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	
	
};
