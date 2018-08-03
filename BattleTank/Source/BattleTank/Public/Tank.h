// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h" //for getWorld
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Tank.generated.h"


class UTankBarrel; //forward declaration 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:
	
	
	//called by the engine when actor damage is dealt(is in explosion radius)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;  //return as health percentage between 0 and 1

	FTankDelegate OnDeath;
	
	void TankExplosion(bool Death,  FVector TankLocation, FRotator TankRotation);

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		UParticleSystem* DeathExplosion = nullptr;
private:

	ATank();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; //initialised in beginplay


	



	
};
