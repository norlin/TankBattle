// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();
	
	bool GetSightLocation(FVector &HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
	
	UPROPERTY(EditDefaultsOnly)
	float CrosshairPosX = 0.5;
	
	UPROPERTY(EditDefaultsOnly)
	float CrosshairPosY = 0.333;
	
	UPROPERTY(EditDefaultsOnly)
	float SightDistance = 1000000.0;
	
};
