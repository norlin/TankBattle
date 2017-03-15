// norlin

#include "TankBattle.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(LeftTrack || !RightTrack)) {
		return;
	}
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!ensure(LeftTrack || !RightTrack)) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto forwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	auto rotateCross = FVector::CrossProduct(TankForward, AIForwardIntention);
	//UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *GetOwner()->GetName(),  *rotateCross.ToString())

	IntendTurnRight(rotateCross.Z);

	IntendMoveForward(forwardThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *GetOwner()->GetName(),  *moveVector.ToString())
}

