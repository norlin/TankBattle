// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();
	
	Throttle = FMath::Clamp<float>(Throttle, 0, 1);
	
	UE_LOG(LogTemp, Warning, TEXT("%s: throttle %f"), *Name, Throttle);
	
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();
	
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
