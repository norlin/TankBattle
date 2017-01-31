// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "AimComponent.h"


// Sets default values for this component's properties
UAimComponent::UAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAimComponent::SetBarrelReference(UTankBarrel* Barrel) {
	this->Barrel = Barrel;
}

void UAimComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) {
		return;
	}
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	auto foundVelocity = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (foundVelocity) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	} else {
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), time);
	}
}

void UAimComponent::MoveBarrel(FVector AimDirection) {
	auto CurrentRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - CurrentRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
}


