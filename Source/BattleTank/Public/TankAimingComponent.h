// Copyright by Hakan Akkurt

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

//Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet, TSubclassOf<AProjectile> ProjectileBlueprintToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

	EFiringState GetFiringState() const;

	void AimAt(FVector HitLocation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000; // Sensible starting value of 1000 m/s

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 2;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 Roundsleft = 20;

	double LastFireTime = 0;

	FVector AimDirection;

};
