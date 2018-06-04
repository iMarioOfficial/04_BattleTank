

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet) || !ensure(RightTrackToSet)) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	//No need to call super as we're replacing the functionality
	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);  //drive until perpendicular to forward to right in front of tank
	IntendMoveForward(ForwardThrow * 3);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;  //turn until parallel to tank, so facing tank
	IntendTurnRight(RightThrow * 3);


}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw * 3);
	RightTrack->SetThrottle(Throw * 3);
}

void UTankMovementComponent::IntendMoveBackwards(float Throw)
{
	LeftTrack->SetThrottle(Throw * 3);
	RightTrack->SetThrottle(Throw * 3);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw * 2);
	RightTrack->SetThrottle(-Throw * 2);

}

void UTankMovementComponent::IntendTurnLeft(float Throw )
{
	RightTrack->SetThrottle(Throw * 2);
	LeftTrack->SetThrottle(-Throw * 2);
}
