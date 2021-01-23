// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"


// Sets default values
AShootProjectile::AShootProjectile() : ShootSpeed(100.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));

	RootComponent = ProjectileCollision;

	ProjectileMesh->SetupAttachment(ProjectileCollision);
}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
		ProjectileCollision->IgnoreActorWhenMoving(GetOwner(), true);

	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
}


void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !Cast<APawn>(OtherActor)) return;
	if (!GetOwner()) return;

	UPrimitiveComponent* OthActor = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
	UPrimitiveComponent* Ownere = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (OthActor->GetCollisionObjectType() == Ownere->GetCollisionObjectType()) return;

	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner) return;

	AController* MyInstigator = PawnOwner->GetController();

	UGameplayStatics::ApplyDamage(OtherActor, Damage, MyInstigator, this, UDamageType::StaticClass());

	Destroy();
}


// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ShootSpeed * DeltaTime, 0.f, 0.f));
}

