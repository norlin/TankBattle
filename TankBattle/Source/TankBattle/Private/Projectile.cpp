// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComponent"));
	MovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionFOrce"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed) {
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &Hit) {
	LaunchBlast->Deactivate();
	ImpactBlast->Activate(true);
	ExplosionForce->FireImpulse();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AProjectile::OnDestroyTimer, DestroyTimeout);
}

void AProjectile::OnDestroyTimer() {
	Destroy();
}
