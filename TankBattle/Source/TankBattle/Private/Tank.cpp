// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "AimComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Tank.h"


// Sets default values
ATank::ATank() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	TankAimComponent = FindComponentByClass<UTankAimComponent>();
}

void ATank::AimAt(FVector HitLocation) {
	if (!ensure(TankAimComponent)) {
		return;
	}
	TankAimComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("Fire! %s"), *name);
	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Warning, TEXT("Fire: No barrel!"));
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
