// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

 UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

 void UTankTrack::BeginPlay()
 {
	 Super::BeginPlay();
	 OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
 }

 void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
 {
	 DriveTrack();
	ApplySidewaysForce();
	//reset throttle
	CurrentThrottle = 0;
 }

 void UTankTrack::ApplySidewaysForce()
 {
	 //calculate slippage speed
	 auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	 //work-out the required acceleration this frame to correct this
	 auto DeltaTime = GetWorld()->GetDeltaSeconds();
	 auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //acceleration this frame, in the opposite direction of the slippage
																				  //Calculate and apply sideways f (f=ma)
	 auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	 auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;

	 TankRoot->AddForce(CorrectionForce);
 }
 void UTankTrack::SetThrottle(float Throttle)
{
	 CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

 void UTankTrack::DriveTrack()
 {
	 auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	 auto ForceLocation = GetComponentLocation();
	 auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // cast so we can add forces to it
	 TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
 }


