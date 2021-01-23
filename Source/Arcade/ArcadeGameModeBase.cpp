// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ArcadeGameModeBase.h"
#include "Arcade/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EnemySpawnComponent.h"
#include "Components/GameHealthComponent.h"
#include "Engine/World.h"

AArcadeGameModeBase::AArcadeGameModeBase()
	:
	PlayerRespawnTime(3.f), IsGameOver(false), ShootLevel(0), ChangeDifficultyTime(3.f)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemiesSpawnController"));

	GameHealthComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("GameHealthComponent"));
}

void AArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (GameHealthComponent)
		GameHealthComponent->EndedGame.AddDynamic(this, &AArcadeGameModeBase::OnPlayerKilled);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;

	PlayerPawn->ShootComponent->ShootInfos = ShootLevelsInfos[ShootLevel].ShootInfos;

	PlayerPawn->PlayerDamaged.AddDynamic(this, &AArcadeGameModeBase::PlayerDamaged);

	GetWorld()->GetTimerManager().SetTimer(ChangeDifficultyTimer, this, &AArcadeGameModeBase::ChangeEnemySpawnDifficulty, ChangeDifficultyTime, true);
}

void AArcadeGameModeBase::OnPlayerKilled()
{
	IsGameOver = true;

	EnemySpawnController->SetActive(false);

	GameOver.Broadcast();
}

void AArcadeGameModeBase::PlayerRespawn()
{
	PlayerPawn->RespawnPlayer();
}

void AArcadeGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

void AArcadeGameModeBase::ChangeEnemySpawnDifficulty()
{
	EnemySpawnController->StageDifficulty = FMath::Max(EnemySpawnController->StageDifficulty * 0.95, 0.35);
}

void AArcadeGameModeBase::ChangeShootLevel(bool Up)
{
	ShootLevel = FMath::Clamp(ShootLevel + (Up ? 1 : -1), 0, ShootLevelsInfos.Num() - 1);

	PlayerPawn->ShootComponent->ShootInfos = ShootLevelsInfos[ShootLevel].ShootInfos;
}

int AArcadeGameModeBase::GetPoints()
{
	return GamePoints;
}

void AArcadeGameModeBase::PlayerDamaged()
{
	GameHealthComponent->ChangeHealth(-1);

	PlayerPawn->ExplodePlayer();

	ChangeShootLevel(false);

	if (!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(PlayerRespawnTimer, this, &AArcadeGameModeBase::PlayerRespawn, PlayerRespawnTime, false);
}