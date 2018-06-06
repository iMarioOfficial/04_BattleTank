// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"   //header for Barrel
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"   //header for suggestprojectilevel
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h" //for getWorld
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
class AProjectile;
class UTankBarrel; 
class UTurret;

//Holds barrel properties 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
		
private:	
	
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UTankBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;  //forces the projectile selection in blueprint to be derrived from the projectile class


	float ReloadTime = 3;
	double LastFireTime = 0;


	FVector AimDirection;
	bool isBarrelMoving();
	
	FVector WhereToAim;
};
