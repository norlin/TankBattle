// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "AimComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TankAimComponent = CreateDefaultSubobject<UAimComponent>(FName("AimComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation) {
	TankAimComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* NewBarrel) {
	TankAimComponent->SetBarrelReference(NewBarrel);
	this->Barrel = NewBarrel;
}

void ATank::SetTurretReference(UTankTurret* NewTurret) {
	TankAimComponent->SetTurretReference(NewTurret);
}

void ATank::Fire() {
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;
	
	if (Barrel && isReloaded) {
		LastFireTime = GetWorld()->GetTimeSeconds();
		
		FVector SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));
		
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation);
		
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}
