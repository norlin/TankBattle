// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();

	//UE_LOG(LogTemp, Warning, TEXT("%s, %s, %s, %f, %f"), *GetOwner()->GetName(), *ForceApplied.ToString(), *GetForwardVector().ToString(), Throttle, TrackMaxForce)
	
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	DrawDebugLine(GetWorld(), ForceLocation, ForceApplied, FColor::Blue, false, -1.f, 0, 50.f);
}
