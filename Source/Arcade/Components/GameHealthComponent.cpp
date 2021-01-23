// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent() : Health(3)
{
}

// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (!PlayerPawn) return;
}

int UGameHealthComponent::GetHealth()
{
	return Health;
}

void UGameHealthComponent::ChangeHealth(int Value)
{
	Health = FMath::Clamp(Health + Value, 0, 5);

	if (Health <= 0)
		EndedGame.Broadcast();
}

