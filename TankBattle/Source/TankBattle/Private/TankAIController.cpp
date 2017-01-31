// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (PlayerTank) {
		auto Tank = Cast<ATank>(GetPawn());
		
		Tank->AimAt(PlayerTank->GetActorLocation());
		Tank->Fire();
	}
}
