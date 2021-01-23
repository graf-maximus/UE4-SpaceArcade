// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDamagedEvent);

UCLASS()
class ARCADE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector TouchLocation);
	void OnTouchPressed(ETouchIndex::Type FingerIndex, FVector TouchLocation);

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY()
		FTimerHandle RespawnTimer;

	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

private:

	FVector2D TouchLocation;

	APlayerController* PlayerController;

	UMaterialInterface* PlayerDefaultMaterial;

	FVector2D ViewportSize;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool ActivatedShield = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* PlayerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UBoxComponent* PlayerCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
		float TouchMoveSensivity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		class UShootComponent* ShootComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game Health")
		FPlayerDamagedEvent PlayerDamaged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UMaterialInterface* PlayerRespawnMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Parameters")
		float MinY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Parameters")
		float MaxY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Parameters")
		float MinX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Parameters")
		float MaxX;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shooting")
		void RespawnPlayer();
		void RespawnPlayer_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Shooting")
		void ExplodePlayer();
		void ExplodePlayer_Implementation();
};
