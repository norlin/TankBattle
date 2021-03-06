// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "AimComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto name = GetPawn()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *name);

	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimComponent)) {
		return;
	}

	FoundAimingComponent(AimComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);

	if (!InPawn) {
		return;
	}

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) {
		return;
	}

	PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) {
		return;
	}

	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();
	if (!ensure(AimComponent)) {
		return;
	}

	FVector HitLocation;
	if (GetSightLocation(HitLocation)) {
		AimComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightLocation(FVector& HitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto AimPosition = FVector2D(ViewportSizeX * CrosshairPosX, ViewportSizeY * CrosshairPosY);

	FVector LookDirection;
	if (GetLookDirection(AimPosition, LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;

	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + LookDirection * SightDistance;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Camera)) {
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
}

void ATankPlayerController::OnTankDeath() {
	StartSpectatingOnly();
}
