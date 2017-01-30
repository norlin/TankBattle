// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {

	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Elevate to %f"), time, RelativeSpeed);
}

