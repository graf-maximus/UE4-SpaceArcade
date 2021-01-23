// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinBonus.h"
#include "Arcade/ArcadeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

ACoinBonus::ACoinBonus() :
	CollectPoints(5)
{
}

void ACoinBonus::CollectedBonus_Implementation()
{
	GameMode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	
	GameMode->AddPoints(CollectPoints);

	Super::CollectedBonus_Implementation();
}