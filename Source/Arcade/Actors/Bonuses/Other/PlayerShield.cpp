// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShield.h"
#include "Engine/World.h"
#include "Arcade/PlayerPawn.h"
#include "Arcade/Actors/Enemies/EnemyPawn.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
APlayerShield::APlayerShield() :
	DeactivateTime(5.f)
{
}

void APlayerShield::ActivateShield(APlayerPawn* PlayerPawn)
{
	GetWorld()->GetTimerManager().ClearTimer(DeactivateTimer);

	BasePawn = PlayerPawn;
	PlayerPawn->ActivatedShield = true;
	PlayerPawn->SetCanBeDamaged(false);

	FAttachmentTransformRules AttachTransformRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
		);

	AttachToActor(PlayerPawn, AttachTransformRules);

	GetWorld()->GetTimerManager().SetTimer(DeactivateTimer, this, &APlayerShield::DeactivateShield, DeactivateTime, false);
}

void APlayerShield::DeactivateShield()
{
	BasePawn->SetCanBeDamaged(true);
	BasePawn->ActivatedShield = false;

	GetWorld()->GetTimerManager().ClearTimer(DeactivateTimer);

	Destroy();
}

