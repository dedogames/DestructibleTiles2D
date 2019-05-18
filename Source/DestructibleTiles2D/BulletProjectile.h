// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.generated.h"

UCLASS()
class DESTRUCTIBLETILES2D_API ABulletProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletProjectile();

	TArray<TEnumAsByte<EObjectTypeQuery> > TypeObj;
	float ProjectileSpeed;
	float ExplosionRadius;
	float ProjectileRadius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class USphereComponent* SphereCP;
	class UPaperSpriteComponent* BulletCP;
	class UProjectileMovementComponent* ProjMovimentCP;

	
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void DestroyActor();
};
