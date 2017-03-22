// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AimComponent.generated.h"

UENUM()
enum class EAimState: uint8 {
	Reloading,
	Aiming,
	Ready
};

class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankAimComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	EAimState GetState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimState AimState = EAimState::Reloading;

private:
	UTankAimComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrel(FVector AimDirection);
	bool isBarrelMoving();

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; // 40 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;
	FVector AimDirection = FVector::ZeroVector;
};
