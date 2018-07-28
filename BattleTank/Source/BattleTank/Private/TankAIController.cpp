// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"  //so we can implement ondeath
//depends on movement component via pathfinding


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

 void ATankAIController::Tick(float DeltaTime)  {

	 Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	//Move towards Player
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius is in cm
		 
	//Aim at Player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
		 
	//Fire at player
	auto FiringState = AimingComponent->GetFiringState();

	if(FiringState == EFiringState::Locked)
	AimingComponent->Fire(); 
	 


}

 void ATankAIController::SetPawn(APawn* InPawn)
 {
	 Super::SetPawn(InPawn);

	 if (InPawn)
	 {
		 auto PossessedTank = Cast<ATank>(InPawn);
		 if (!ensure(PossessedTank)) { return; }

		 PossessedTank->OnDeath().AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	 }

 }

 void ATankAIController::OnPossesedTankDeath()
 {
	 UE_LOG(LogTemp, Warning, TEXT("RECEIVED!"))

 }




