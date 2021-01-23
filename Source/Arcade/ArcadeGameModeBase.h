// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "Arcade/Components/ShootComponent.h"
#include "Arcade/Actors/Bonuses/Other/PlayerShield.h"
#include "ArcadeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

USTRUCT(BlueprintType)
struct FShootLevelInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		TArray<FShootInfo> ShootInfos;
};

UCLASS()
class ARCADE_API AArcadeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AArcadeGameModeBase();

protected:

	virtual void BeginPlay() override;

	class APlayerPawn* PlayerPawn;

	float PlayerRespawnTime;
	FTimerHandle PlayerRespawnTimer;

	float ChangeDifficultyTime;
	FTimerHandle ChangeDifficultyTimer;

	int GamePoints;

	bool IsGameOver;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enemies")
		class UEnemySpawnComponent* EnemySpawnController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Health")
		class UGameHealthComponent* GameHealthComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game")
		FGameOverEvent GameOver;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		TArray<FShootLevelInfo> ShootLevelsInfos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		int ShootLevel;

	UFUNCTION()
		void PlayerDamaged();

	UFUNCTION()
		void PlayerRespawn();

	UFUNCTION()
		void AddPoints(int Points);

	UFUNCTION()
		void ChangeEnemySpawnDifficulty();

	UFUNCTION()
		void ChangeShootLevel(bool Up);

	UFUNCTION(BlueprintCallable, Category = "Game")
		void OnPlayerKilled();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Points")
		int GetPoints();
};
