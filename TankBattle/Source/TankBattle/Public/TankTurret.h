// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);
	
private:
	UPROPERTY(Category=Setup, EditDefaultsOnly)
	float MaxDegreesPerSecond = 25.f;
	
};
