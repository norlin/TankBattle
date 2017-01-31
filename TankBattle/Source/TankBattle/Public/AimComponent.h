// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AimComponent.generated.h"

class UTankTurret;
class UTankBarrel;

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimComponent();

	void SetTurretReference(UTankTurret* NewTurret);
	void SetBarrelReference(UTankBarrel* NewBarrel);
	void AimAt(FVector HitLocation, float LaunchSpeed);
	
private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	
	void MoveBarrel(FVector AimDirection);
	
};
