// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("Can't find player tank!"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Player tank is: %s!"), *(PlayerTank->GetName()));
	}
	
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	
	auto PC = GetWorld()->GetFirstPlayerController();
	
	if (!PC) {
		return nullptr;
	}
	
	auto PlayerTank = Cast<ATank>(PC->GetPawn());
	
	if (!PlayerTank) {
		return nullptr;
	}
	
	return PlayerTank;
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
}
