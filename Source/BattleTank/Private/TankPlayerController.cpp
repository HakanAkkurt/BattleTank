// Copyright by Hakan Akkurt

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::SetPawn(APawn* InPawn) {

    Super::SetPawn(InPawn);
    if (InPawn) {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank) { return; }

        // Subscribe our local method to the tank`s death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}

void ATankPlayerController::OnPossessedTankDeath() {
    StartSpectatingOnly();
}


void ATankPlayerController::BeginPlay(){
    
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }

    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime){

    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair(){

    if (!GetPawn()) { return; } // e.g. if not possessing
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }

    FVector HitLocation;
    bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
    if(bGotHitLocation){ //Has "side-effect", is going to line trace

        AimingComponent->AimAt(HitLocation);
    }


}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const{

    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection)){
 
        return GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }

    return false;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const{

    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceTange);
    if(GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility
    )){
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const{

FVector CameraWorldLocation;
return DeprojectScreenPositionToWorld(
    ScreenLocation.X,
    ScreenLocation.Y,
    CameraWorldLocation,
    LookDirection);
}