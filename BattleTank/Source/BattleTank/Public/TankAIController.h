// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
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

private:		
		virtual void Tick(float DeltaTime) override;
		
		


	
};
