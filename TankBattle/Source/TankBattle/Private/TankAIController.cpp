// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "AimComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) || !ensure(ControlledTank)) {
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimComponent = ControlledTank->FindComponentByClass<UTankAimComponent>();
	AimComponent->AimAt(PlayerTank->GetActorLocation());
		
	// TODO: call Fire only after aiming completed
	if (AimComponent->GetState() == EAimState::Ready) {
		AimComponent->Fire();
	}
}
