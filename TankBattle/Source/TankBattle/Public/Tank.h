// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UAimComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()
	
public:
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* NewTurret);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* NewBarrel);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void Fire();
	
protected:
	UAimComponent* TankAimComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000; // 40 m/s
	
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	float ReloadTime = 3;
	double LastFireTime = 0;
};
