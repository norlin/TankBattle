// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimComponent;
class UTankMovementComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class TANKBATTLE_API ATank : public APawn {
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Input)
	void Fire();

protected:
	UPROPERTY(EditAnywhere)
	UTankAimComponent* TankAimComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; // 40 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr;
};
