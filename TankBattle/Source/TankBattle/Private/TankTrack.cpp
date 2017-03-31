// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewayForce() {
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	
	auto tank = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (tank->GetMass() * CorrectionAcceleration) / 2;

	// DrawDebugLine(GetWorld(), tank->GetComponentLocation(), CorrectionForce, FColor::Red, false, -1.f, 0, 50.f);

	tank->AddForce(CorrectionForce);
}

void UTankTrack::DriveTank() {
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxForce;
	auto ForceLocation = GetComponentLocation();

	// DrawDebugLine(GetWorld(), ForceLocation, ForceApplied, FColor::Blue, false, -1.f, 0, 50.f);

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + FMath::Clamp<float>(Throttle, -1, 1), -2, 2);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &Hit) {
	DriveTank();
	ApplySidewayForce();
	CurrentThrottle = 0;
}
