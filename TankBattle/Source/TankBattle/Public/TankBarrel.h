// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(Category=Setup, EditDefaultsOnly)
	float MaxDegreesPerSecond = 10.f;
	
	UPROPERTY(Category=Setup, EditDefaultsOnly)
	float MaxElevation = 40.f;
	
	UPROPERTY(Category=Setup, EditDefaultsOnly)
	float MinElevation = 0.f;
	
};
