// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "Components/SphereComponent.h"
#include "Arcade/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	SetRootComponent(Collision);

	Collision->SetSphereRadius(50.f);
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor) return;
	if (!Cast<APlayerPawn>(OtherActor)) return;

	CollectedBonus();
}

void ABonus::CollectedBonus_Implementation()
{
	if (CollectParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform());

	Destroy();
}

void ABonus::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float WorldOffset = -300.f * DeltaSeconds;
	
	AddActorWorldOffset(FVector(WorldOffset, 0.f, 0.f));
}
