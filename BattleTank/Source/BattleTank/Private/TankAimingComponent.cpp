// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;

}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	if (!Barrel) { return; }     //if there is no barrel then fail

	FVector OutLaunchVelocity;                                                                            //setting up variables for SuggestProjectileVelocity()
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	
	if ( UGameplayStatics::SuggestProjectileVelocity					//Calculate the OutLaunchVelocity
			(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
			)
	   )		
	
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //turns the launch velocity into a direction (green arrow to white one from the slides)
		auto TankName = GetOwner()->GetName();

		UE_LOG(LogTemp, Warning, TEXT("%s Aiming At %s"),*TankName, *AimDirection.ToString());  //telling us which direction to aim if we wanna hit whatever we're aiming at
	
	}	//if no solution then do nothing


	         



}


