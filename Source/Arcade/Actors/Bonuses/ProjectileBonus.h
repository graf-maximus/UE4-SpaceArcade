// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "ProjectileBonus.generated.h"

/**
 * 
 */
UCLASS()
class ARCADE_API AProjectileBonus : public ABonus
{
	GENERATED_BODY()

protected:

	virtual void CollectedBonus_Implementation() override;
	
};
