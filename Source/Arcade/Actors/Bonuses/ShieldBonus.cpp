// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBonus.h"
#include "Arcade/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AShieldBonus::CollectedBonus_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;

	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);
	if (!PlayerPawn) return;

	FActorSpawnParameters ShieldSpawnInfo;
	ShieldSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* ActiveShield = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerShield::StaticClass());
	Shield = Cast<APlayerShield>(ActiveShield);
	
	if (!Shield)
	{
		Shield = GetWorld()->SpawnActor<APlayerShield>(APawnShield, ShieldSpawnInfo);
		if (!Shield) return;
	}

	Shield->ActivateShield(PlayerPawn);

	Super::CollectedBonus_Implementation();
}
