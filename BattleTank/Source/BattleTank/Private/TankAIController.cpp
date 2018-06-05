// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
//depends on movement component via pathfinding


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

 void ATankAIController::Tick(float DeltaTime)  {

	 Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
 
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	 
	// Move towards to player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius is in cm
		 
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
		 
	//Fire If ready
	AimingComponent->Fire(); 
	 


}






