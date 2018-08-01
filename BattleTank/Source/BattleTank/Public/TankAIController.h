// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
		virtual void BeginPlay() override;

protected:
	//How close AI Tank get to player
		UPROPERTY(EditDefaultsOnly, Category = "Setup") 
		float AcceptanceRadius = 4000; //40m  
		
		UPROPERTY(EditDefaultsOnly, Category = "Explosion")
			UParticleSystem* DeathExplosion = nullptr;

private:		
		virtual void Tick(float DeltaTime) override;
		
		virtual void SetPawn(APawn* InPawn) override;

		UFUNCTION()
			void OnPossessedTankDeath();
	
		
};
