// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h" //for getWorld
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel; //forward declaration 



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()



private:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//sets default values
	ATank();





	
};
