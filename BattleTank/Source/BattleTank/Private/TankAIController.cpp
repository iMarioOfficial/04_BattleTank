// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"





void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find a player tank!"));                             //all of this playertank thing is to find a human player tank onto which to aim
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank  :%s"), *(PlayerTank->GetName()));
	}
	
}

 void ATankAIController::Tick(float DeltaTime)  {

	 Super::Tick(DeltaTime);

	 if (GetPlayerTank())    
	 {
		 //TODO Move towards to player
		 
		 
		 // Aim towards the player
		 GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		 
		 //Fire If ready

	 }


}

ATank * ATankAIController::GetPlayerTank() const       //finds the player's, not AI's tank
{

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }      // if null pointer, leave!!
	
	return Cast<ATank>(PlayerPawn);

}





ATank* ATankAIController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());


}
