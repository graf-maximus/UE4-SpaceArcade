// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundBorder.h"
#include "Components/BoxComponent.h"
#include "Arcade/PlayerPawn.h"

// Sets default values
APlaygroundBorder::APlaygroundBorder()
{
	BorderCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BorderCollision"));
	BorderCollision->SetCollisionProfileName("OverlapAll");
	SetRootComponent(BorderCollision);
}

void APlaygroundBorder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor) return;
	if (Cast<APlayerPawn>(OtherActor)) return;

	OtherActor->Destroy();
}
