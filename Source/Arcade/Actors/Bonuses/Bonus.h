// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Bonus.generated.h"

UCLASS()
class ARCADE_API ABonus : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABonus();

protected:

	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void CollectedBonus();
		virtual void CollectedBonus_Implementation();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bonus")
		class USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* CollectParticle;
};