// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "AimComponent.h"

UTankAimComponent::UTankAimComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) {
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel) || !ensure(Turret)) {
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	auto foundVelocity = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (foundVelocity) {
		AimState = EAimState::Aiming;

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	} else {
		AimState = EAimState::Ready;
	}
}

void UTankAimComponent::MoveBarrel(FVector AimDirection) {
	if (!ensure(Barrel || !Turret)) {
		return;
	}

	auto CurrentRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - CurrentRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimComponent::Fire() {
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Fire! %s"), *name);
	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Warning, TEXT("Fire: No barrel!"));
		return;
	}

	if (!ensure(ProjectileBlueprint)) {
		UE_LOG(LogTemp, Warning, TEXT("Fire: No Projectile!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Fire available!"));

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;

	if (isReloaded) {
		LastFireTime = GetWorld()->GetTimeSeconds();

		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);

		Projectile->LaunchProjectile(LaunchSpeed);
	}
}