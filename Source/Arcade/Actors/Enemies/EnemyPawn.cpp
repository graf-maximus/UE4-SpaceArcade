// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade/Components/ShootComponent.h"
#include "Arcade/Components/HealthComponent.h"
#include "Arcade/ArcadeGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyCollision"));
	RootComponent = EnemyCollision;
	EnemyCollision->SetCollisionProfileName("Pawn");

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyrMesh"));
	EnemyMesh->SetupAttachment(EnemyCollision);
	EnemyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootingComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::OnDestroyEvent);

	for (UActorComponent* EngineComponent : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
		EngineComponent->Activate(true);
	
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::OnDestroyEvent()
{
	AArcadeGameModeBase* GameMode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(EnemyPoints);

	for (UActorComponent* EngineComponent : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
		EngineComponent->Deactivate();

	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform());

	DropBonuses();

	Destroy();
}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;
	if (!UGameplayStatics::GetPlayerPawn(this, 0)->CanBeDamaged()) return;

	AArcadeGameModeBase* GameMode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;

	GameMode->ChangeShootLevel(false);

	UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());

	OnDestroyEvent();
}

void AEnemyPawn::DropBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	float RandomValue = Random.RandRange(0.f, 100.f);

	for (FBonuses& Bonus : PossibleBonuses)
	{
		if (RandomValue < Bonus.DropChance)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.AdditionalBonus, GetActorLocation(), FRotator(0.f, 0.f, 0.f), SpawnParameters);
		}
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -100.f * DeltaTime;

	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

