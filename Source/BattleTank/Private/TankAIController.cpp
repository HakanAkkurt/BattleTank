// Copyright by Hakan Akkurt

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"
#include "Tank.h"

void ATankAIController::BeginPlay(){
    
    Super::BeginPlay();   
}

void ATankAIController::SetPawn(APawn* InPawn) {

    Super::SetPawn(InPawn);
    if (InPawn) {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }

        // Subscribe our local method to the tank`s death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath() {

    UE_LOG(LogTemp, Warning, TEXT("Received!"));
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

