// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
	: Health(100.f)
{}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerDamage);
}

void UHealthComponent::OnOwnerDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Insigator, AActor* DamageCauser)
{
	ChangeHealth(-Damage);
}

void UHealthComponent::ChangeHealth(float Value)
{
	Health += Value;
	
	if (Health <= 0.f)
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerDamage);

		OnHealthEnded.Broadcast();
	}
}

float UHealthComponent::GetHealth()
{
	return Health;
}

