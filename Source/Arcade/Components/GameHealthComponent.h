// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndedEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UGameHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game Health")
		int Health;

public:	

	UFUNCTION(BlueprintCallable, Category = "Game Health")
		int GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Game Health")
		void ChangeHealth(int Value);
		
	UPROPERTY(BlueprintAssignable, Category = "GameHealth")
		FGameEndedEvent EndedGame;
};
