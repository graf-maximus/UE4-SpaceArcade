// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBonus.h"
#include "Arcade/ArcadeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade/Components/GameHealthComponent.h"

void AHealthBonus::CollectedBonus_Implementation()
{
	AArcadeGameModeBase* GameMode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;

	GameMode->GameHealthComponent->ChangeHealth(1);

	Super::CollectedBonus_Implementation();
}
