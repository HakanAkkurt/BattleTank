// Copyright by Hakan Akkurt

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

class UTankAimingComponent;
/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	protected:
		UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

		UFUNCTION()
		void OnPossessedTankDeath();

	private:
		void SetPawn(APawn* InPawn);


		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

		/*Start the tank moving the barrel so that a shout would hit where
		the crosshairs intersects the world.*/
		void AimTowardsCrosshair();

		bool GetSightRayHitLocation(FVector& OutHitLocation) const;

		UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;

		UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333;

		UPROPERTY(EditDefaultsOnly)
		float LineTraceTange = 1000000;

		bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
		bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
