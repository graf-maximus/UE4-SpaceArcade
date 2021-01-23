// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "Arcade/Actors/Projectiles/ShootProjectile.h"
#include "ShootComponent.generated.h"


USTRUCT(BlueprintType)
struct FShootInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AShootProjectile> ProjectileClass;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle ShootingTimer;

	
	void Shoot();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		float ShootPeriod;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
		void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
		void StopShooting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* ShootParticle;
};
