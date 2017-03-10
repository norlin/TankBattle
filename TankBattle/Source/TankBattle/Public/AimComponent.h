// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AimComponent.generated.h"

UENUM()
enum class EAimState: uint8
{
	Reloading,
	Aiming,
	Ready
};

class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimState AimState = EAimState::Ready;
	
private:
	UTankAimComponent();

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	
	void MoveBarrel(FVector AimDirection);
};
