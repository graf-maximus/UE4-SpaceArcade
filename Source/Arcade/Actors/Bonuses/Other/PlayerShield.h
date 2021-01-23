// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "PlayerShield.generated.h"

class APlayerPawn;
class AEnemyPawn;

UCLASS()
class ARCADE_API APlayerShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerShield();

protected:

	APlayerPawn* BasePawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shield")
		float DeactivateTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shield")
		FTimerHandle DeactivateTimer;

public:

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void ActivateShield(APlayerPawn* PlayerPawn);

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void DeactivateShield();
};
