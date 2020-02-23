// Copyright by Hakan Akkurt

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet){
    RightTrack = RightTrackToSet;
    LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed){
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

    IntendMoveForward(ForwardThrow);
    IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw){
    if(!ensure(RightTrack && LeftTrack)) { return; }
    RightTrack->SetThrottle(Throw);
    LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw){
    if(!ensure(RightTrack && LeftTrack)) { return; }
    RightTrack->SetThrottle(-Throw);
    LeftTrack->SetThrottle(Throw);
}