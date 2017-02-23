// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxForce = 400000; // assume 40 tonne tank and 1g acceleration
};
