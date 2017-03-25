// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "AimComponent.h"

UTankAimComponent::UTankAimComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimComponent::BeginPlay() {
	LastFireTime = GetWorld()->GetTimeSeconds();
	AmmoLeft = AmmoCount;
}

void UTankAimComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet) {
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if (AmmoLeft == 0) {
		AimState = EAimState::OutOfAmmo;
		return;
	}
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime) {
		AimState = EAimState::Reloading;
	} else if (isBarrelMoving()) {
		AimState = EAimState::Aiming;
	} else {
		AimState = EAimState::Ready;
	}
}

void UTankAimComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel) || !ensure(Turret)) {
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	auto foundVelocity = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (foundVelocity) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimComponent::MoveBarrel(FVector AimDirectionToSet) {
	if (!ensure(Barrel) || !ensure(Turret)) {
		return;
	}

	auto CurrentRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirectionToSet.Rotation();
	auto DeltaRotator = AimRotator - CurrentRotator;

	Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}

bool UTankAimComponent::isBarrelMoving() {
	if (!ensure(Barrel) || !ensure(Turret)) {
		return false;
	}

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimComponent::Fire() {
	auto name = GetOwner()->GetName();
	if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) {
		return;
	}

	if (AimState == EAimState::OutOfAmmo) {
		UE_LOG(LogTemp, Warning, TEXT("Out of Ammo!"));
		return;
	}

	if (AimState == EAimState::Ready || AimState == EAimState::Aiming) {
		LastFireTime = GetWorld()->GetTimeSeconds();

		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));

		AmmoLeft -= 1;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);

		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

EAimState UTankAimComponent::GetState() const {
	return AimState;
}

int32 UTankAimComponent::GetAmmoLeft() const {
	return AmmoLeft;
}
