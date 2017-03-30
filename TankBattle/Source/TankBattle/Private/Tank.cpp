// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"

// Sets default values
ATank::ATank() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	CurrentHealth = Health;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	float Damage = FMath::Clamp(DamageAmount, 0.f, CurrentHealth);

	CurrentHealth -= Damage;

	if (CurrentHealth == 0.f) {
		auto name = GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is dead!"), *name);
	}

	return Damage;
}

float ATank::GetCurrentHealth() const {
	return CurrentHealth;
}

float ATank::GetHealthPercent() const {
	return CurrentHealth / Health;
}
