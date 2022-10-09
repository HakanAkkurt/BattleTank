// Copyright by Hakan Akkurt

#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float RelativeSpeed){

    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

    SetRelativeRotation(FRotator(Elevation, 0, 0));

}
