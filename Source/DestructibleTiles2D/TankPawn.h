/*
	Project: Destructible Tiles 2D
	Developer: Gelson G. Rodrigues
	Date: 05-10-2019
	***************
	* Description *
	***************

	Game Mode

	************************
	*    Improvements	   *
	************************
	************************
	*    Changes   	       *
	************************
	Date		 Developer			Description
	--------------------------------------------------
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

UCLASS()
class DESTRUCTIBLETILES2D_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:

	void IncreaseSpeed(float Val);
	void RotateCannon();
	void PredictPath();
	void Fire();

	/*
		 @@object_type_query_1: EObjectTypeQuery!int(0) // world static
		 @@object_type_query_2: EObjectTypeQuery!int(1) // world dynamic
		 @@object_type_query_3: EObjectTypeQuery!int(2) // pawn
		 @@object_type_query_4: EObjectTypeQuery!int(3) // physics body
		 @@object_type_query_5: EObjectTypeQuery!int(4) // vehicle
		 @@object_type_query_6: EObjectTypeQuery!int(5) // destructible 
	*/
	TArray<TEnumAsByte<EObjectTypeQuery> > TypeObj;

	float ProjectileRadius;
	float LaunchVelocity;
	
	float ExplosionRadius;

	/* Projectil Ref*/
	class ABulletProjectile* CurrentProject;

	/*Copmponents*/
	class USceneComponent* RootCP;
	class UPaperSpriteComponent* Tank_Part1CP;
	class UPaperSpriteComponent* Tank_Part2CP;
	class UPaperSpriteComponent* Tank_Part3CP;
	class UPaperSpriteComponent* ArrowCP;
	class USceneComponent* ShooterCP;

};
