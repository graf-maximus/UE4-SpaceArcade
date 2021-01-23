// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arcade/Actors/Bonuses/Bonus.h"
#include "EnemyPawn.generated.h"

USTRUCT(BlueprintType)
struct FBonuses
{
	GENERATED_BODY()
			
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonuses")
		TSubclassOf<ABonus> AdditionalBonus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonuses")
		float DropChance;
};

UCLASS()
class ARCADE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnEnemyOverlap(AActor* OverlappedComponent, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
		float EnemyPoints;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnDestroyEvent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* EnemyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* EnemyCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		class UShootComponent* ShootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonuses")
		TArray<FBonuses> PossibleBonuses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* DestroyParticle;

	UFUNCTION(Category = "Bonuses")
		void DropBonuses();
};
