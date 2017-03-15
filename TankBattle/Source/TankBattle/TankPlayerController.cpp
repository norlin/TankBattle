// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "AimComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	
	auto AimComponent = GetControlledTank()->FindComponentByClass<UTankAimComponent>();
	if (ensure(AimComponent)) {
		FoundAimingComponent(AimComponent);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No AimComponent found!"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}
	
	FVector HitLocation;
	if (GetSightLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightLocation(FVector &HitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	auto AimPosition = FVector2D(ViewportSizeX * CrosshairPosX, ViewportSizeY * CrosshairPosY);
	
	FVector LookDirection;
	if (GetLookDirection(AimPosition, LookDirection)) {
		if (GetLookVectorHitLocation(LookDirection, HitLocation)) {
			return true;
		}
	}
	
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const {
	FHitResult HitResult;
	
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + LookDirection*SightDistance;
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	
	HitLocation = FVector(0);
	return false;
}
