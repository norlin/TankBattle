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

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) || !ensure(ControlledTank)) {
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
		UE_LOG(LogTemp, Warning, TEXT("SetPawn with no pawn!"));
		return;
	}

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) {
		UE_LOG(LogTemp, Warning, TEXT("Pawn is not ATank!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("TankAI subscribing..."));

	PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);

	UE_LOG(LogTemp, Warning, TEXT("TankAI subscribed to death!"));
}

void ATankAIController::OnTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("Tank is dead! %s"));
}
