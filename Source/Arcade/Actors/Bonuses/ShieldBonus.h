// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "Arcade/Actors/Bonuses/Other/PlayerShield.h"
#include "ShieldBonus.generated.h"

UCLASS()
class ARCADE_API AShieldBonus : public ABonus
{
	GENERATED_BODY()

protected:

	virtual void CollectedBonus_Implementation() override;
	
	APlayerShield* Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
		TSubclassOf<APlayerShield> APawnShield;
};
