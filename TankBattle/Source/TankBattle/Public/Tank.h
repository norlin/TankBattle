// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankEvent);

UCLASS()
class TANKBATTLE_API ATank : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void BeginPlay() override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "State")
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintPure, Category = "State")
	float GetHealthPercent() const;

	FTankEvent OnTankDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Health = 100;

	float CurrentHealth = 0;

};
