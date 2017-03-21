// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	
	auto tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (tank->GetMass() * CorrectionAcceleration) / 2;

	tank->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();

	//UE_LOG(LogTemp, Warning, TEXT("%s, %s, %s, %f, %f"), *GetOwner()->GetName(), *ForceApplied.ToString(), *GetForwardVector().ToString(), Throttle, TrackMaxForce)

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	DrawDebugLine(GetWorld(), ForceLocation, ForceApplied, FColor::Blue, false, -1.f, 0, 50.f);
}
