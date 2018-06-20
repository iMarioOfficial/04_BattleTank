// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth ;  //cast both to floats
}

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0) { UE_LOG(LogTemp, Warning, TEXT("RIP IN PIECES TANK")) }
	UE_LOG(LogTemp, Warning, TEXT("Damage Amount : %f     Damage To Apply=   %i"), DamageAmount, DamageToApply)

	return DamageToApply;
}

