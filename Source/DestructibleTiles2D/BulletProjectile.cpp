// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "ExplosionActor.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperGroupedSpriteComponent.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABulletProjectile::ABulletProjectile()
{
	SphereCP = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = SphereCP;

	SphereCP->bHiddenInGame = false;

	BulletCP = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Bullet"));
	BulletCP->SetupAttachment(SphereCP);

	static ConstructorHelpers::FObjectFinder<UPaperSprite> SpriteObj(TEXT("PaperSprite'/Game/Assets/Sprites/Tank/tank_bulletFly3_Sprite.tank_bulletFly3_Sprite'"));
	if (SpriteObj.Succeeded())
		BulletCP->SetSprite(SpriteObj.Object);

	ProjMovimentCP = CreateDefaultSubobject <UProjectileMovementComponent>(TEXT("ProjectileMoviment"));
	ProjMovimentCP->bRotationFollowsVelocity			  = true;
	ProjMovimentCP->Bounciness							  = 0.0f;
	ProjMovimentCP->Friction						      = 0.0f;
	ProjMovimentCP->BounceVelocityStopSimulatingThreshold = 0.0f;
	 

	ProjectileSpeed  = 500.0f;
	ExplosionRadius  = 200.0f;
	ProjectileRadius = 15;

	SphereCP->SetNotifyRigidBodyCollision(true);


	SphereCP->BodyInstance.SetCollisionProfileName("BlockNoPawn");
	SphereCP->OnComponentHit.AddDynamic(this, &ABulletProjectile::OnCompHit);

}

// Called when the game starts or when spawned
void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjMovimentCP->SetVelocityInLocalSpace(FVector(ProjectileSpeed, 0.0f, 0.0f));
	SphereCP->SetSphereRadius(ProjectileRadius, true);
	
}

void ABulletProjectile::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DestroyActor();
	Destroy();
}

void ABulletProjectile::DestroyActor()
{
	FTransform NewT;

	float div = ExplosionRadius / 50.0;
 
	NewT.SetLocation(FVector(0.0f, 0.0f, 0.0f) + GetActorLocation());
	NewT.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	NewT.SetScale3D(FVector(div, div, div));
	
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AExplosionActor>(AExplosionActor::StaticClass(), NewT, params);

	TArray<UPrimitiveComponent*> OutComponents;
	TArray<AActor*> ActorsToIgnore;
	UKismetSystemLibrary::SphereOverlapComponents(GetWorld(), GetActorLocation(), ExplosionRadius, TypeObj, UPaperGroupedSpriteComponent::StaticClass(), ActorsToIgnore, OutComponents);
 
	for (UPrimitiveComponent* ArrEle : OutComponents)
	{
		UPaperGroupedSpriteComponent * UgroupSprite = Cast<UPaperGroupedSpriteComponent>(ArrEle);
		/* Max Tiles to destroy*/
		int numTilestoDestroy = 3;
		for (int32 i = 0; i < numTilestoDestroy; i++)
		{
			for (int32 j = 0; j < UgroupSprite->GetInstanceCount(); j++)
			{
				FTransform OutInstanceTransform;
				UgroupSprite->GetInstanceTransform(j, OutInstanceTransform, true);


				float VecLength = (OutInstanceTransform.GetLocation() - GetActorLocation()).Size();
				if (VecLength < ExplosionRadius)
				{
					UgroupSprite->RemoveInstance(j);
				}

			}
		}
	}
}
 