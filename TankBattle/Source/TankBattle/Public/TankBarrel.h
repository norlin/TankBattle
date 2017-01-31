// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent), hidecategories=("Collision") )
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(Category=Setup, EditAnywhere)
	float MaxDegreesPerSecond = 10.f;
	
	UPROPERTY(Category=Setup, EditAnywhere)
	float MaxElevation = 40.f;
	
	UPROPERTY(Category=Setup, EditAnywhere)
	float MinElevation = 0.f;
	
};