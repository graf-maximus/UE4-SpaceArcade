// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBonus.h"
#include "Arcade/ArcadeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AProjectileBonus::CollectedBonus_Implementation()
{
	AArcadeGameModeBase* GameMode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;

	GameMode->ChangeShootLevel(true);

	Super::CollectedBonus_Implementation();
}