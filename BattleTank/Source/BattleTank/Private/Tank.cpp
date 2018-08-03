// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth ;  //cast both to floats
}

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DeathExplosionObj(TEXT("ParticleSystem'/Game/Tank/DeathExplosion.DeathExplosion'"));
	if (DeathExplosionObj.Object)
	{
		DeathExplosion = DeathExplosionObj.Object;
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0) 
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

void ATank::TankExplosion(bool Death, FVector TankLocation, FRotator TankRotation)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathExplosion, TankLocation, TankRotation, false, EPSCPoolMethod::None);
}
