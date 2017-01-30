// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AimComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimComponent();

	void SetBarrelReference(UTankBarrel* Barrel);
	void AimAt(FVector HitLocation, float LaunchSpeed);
	
private:
	UTankBarrel* Barrel = nullptr;
	
	void MoveBarrel(FVector AimDirection);
	
};
