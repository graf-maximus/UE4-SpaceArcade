// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "CoinBonus.generated.h"


UCLASS()
class ARCADE_API ACoinBonus : public ABonus
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoinBonus();

private:
	class AArcadeGameModeBase* GameMode;

protected:

	virtual void CollectedBonus_Implementation() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Points")
		int CollectPoints;
};
