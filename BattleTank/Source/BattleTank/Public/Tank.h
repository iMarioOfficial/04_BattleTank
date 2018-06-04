// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h" //for getWorld
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel; //forward declaration 
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
	

private:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//sets default values
	ATank();


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;   

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;  //forces the projectile selection in blueprint to be derrived from the projectile class

	UTankBarrel* Barrel = nullptr; //local reference for spawning projectile

	float ReloadTime = 3;
	double LastFireTime = 0;

	
};
