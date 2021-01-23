// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "Arcade/Actors/Enemies/EnemyPawn.h"
#include "EnemySpawnComponent.generated.h"


USTRUCT(BlueprintType)
struct FEnemyInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int EnemiesAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float SpawnDelay;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Deactivate() override;

	void SpawnEnemy();
	void StartSpawnStage();

	FTimerHandle StageTimer;
	FTimerHandle EnemySpawnTimer;

	FEnemyInfo SpawnStage;

	FRandomStream Random;

	int EnemiesSpawned;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		TArray<FEnemyInfo> EnemyInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		float StageMinDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		float StageMaxDelay;

	UPROPERTY(BlueprintReadOnly, Category = "Spawn")
		float StageDifficulty;
};
