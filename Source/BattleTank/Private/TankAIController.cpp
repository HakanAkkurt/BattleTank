// Copyright by Hakan Akkurt

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay(){
    
    Super::BeginPlay();   
}

void ATankAIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if (!ensure(PlayerTank && ControlledTank)) { return; }

    //Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius);

    //Aim towards the player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
   
    if (AimingComponent->GetFiringState() == EFiringState::Locked) {

        AimingComponent->Fire();
    }

}
