// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ShootComponent.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APlayerPawn::APlayerPawn() : 
	TouchMoveSensivity(2.f), MinX(-550.f), MaxX(1200.f), MinY(-600.f), MaxY(600.f)
{
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));

	PlayerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerCollision"));

	RootComponent = PlayerCollision;
	PlayerMesh->SetupAttachment(PlayerCollision);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootingComponent"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	MaxX = (ViewportSize.Y * 1200) / 967;
	MinX = (ViewportSize.Y * -550) / 967;

	Super::BeginPlay();

	PlayerDefaultMaterial = PlayerMesh->GetMaterial(0);
}

void APlayerPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

float APlayerPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!CanBeDamaged()) return 0.f;

	PlayerDamaged.Broadcast();

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return DamageAmount;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPressed);

	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}

void APlayerPawn::RespawnPlayer_Implementation()
{
	if (!ActivatedShield)
		SetCanBeDamaged(true);
	//SetActorEnableCollision(true);

	PlayerMesh->SetMaterial(0, PlayerDefaultMaterial);
	
	ShootComponent->StartShooting();

	for (UActorComponent* EngineComponent : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
		EngineComponent->Activate(true);
}

void APlayerPawn::ExplodePlayer_Implementation()
{
	SetCanBeDamaged(false);
	//SetActorEnableCollision(false);

	for (UActorComponent* EngineComponent : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
		EngineComponent->Deactivate();

	PlayerMesh->SetMaterial(0, PlayerRespawnMaterial);
}

void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);
	FVector NewLocation = GetActorLocation();

	TouchDeltaMove *= TouchMoveSensivity;

	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, MinX, MaxX);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, MinY, MaxY);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerPawn::OnTouchPressed(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);
}
