// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnComponent.h"
#include "Engine/World.h"

// Called when the game starts
void UEnemySpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	Random.GenerateNewSeed();

	StageDifficulty = 1.f;

	StartSpawnStage();
}

void UEnemySpawnComponent::Deactivate()
{
	Super::Deactivate();

	GetWorld()->GetTimerManager().ClearTimer(StageTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}

void UEnemySpawnComponent::SpawnEnemy()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParameters);

	EnemiesSpawned++;

	if (EnemiesSpawned < SpawnStage.EnemiesAmount)
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnComponent::SpawnEnemy, SpawnStage.SpawnDelay, false);
}

void UEnemySpawnComponent::StartSpawnStage()
{
	SpawnStage = EnemyInfos[Random.RandRange(0, EnemyInfos.Num() - 1)];

	EnemiesSpawned = 0;

	SpawnEnemy();

	float RandomStage = Random.RandRange(StageMinDelay, StageMaxDelay) * StageDifficulty;

	GetWorld()->GetTimerManager().SetTimer(StageTimer, this, &UEnemySpawnComponent::StartSpawnStage, RandomStage, false);
}


