// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "AimComponent.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) {
		return;
	}

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerTank) {
		// TODO: destroy other tanks when no player found
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimComponent = ControlledTank->FindComponentByClass<UTankAimComponent>();
	AimComponent->AimAt(PlayerTank->GetActorLocation());
		
	if (AimComponent->GetState() == EAimState::Ready) {
		AimComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);

	if (!InPawn) {
		return;
	}

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) {
		return;
	}

	PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
}

void ATankAIController::OnTankDeath() {
	auto pawn = GetPawn();
	if (!pawn) {
		return;
	}

	pawn->DetachFromControllerPendingDestroy();
}
