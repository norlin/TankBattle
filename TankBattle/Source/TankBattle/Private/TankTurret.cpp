// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Rotate to %f"), time, RelativeSpeed);
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	
	if (RawNewRotation >= 360) {
		RawNewRotation = RawNewRotation - 360;
	} else if (RawNewRotation <= -360) {
		RawNewRotation = RawNewRotation + 360;
	}
	
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
