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

#include "TankPawn.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "DrawDebugHelpers.h"
#include "BulletProjectile.h"

// Sets default values
ATankPawn::ATankPawn()
{ 
	PrimaryActorTick.bCanEverTick = true;

	RootCP = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootCP;

	Tank_Part1CP = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Tank_Par1"));
	Tank_Part1CP->SetupAttachment(RootCP);

	Tank_Part2CP = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Tank_Par2"));
	Tank_Part2CP->SetupAttachment(RootCP);

	Tank_Part3CP = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Tank_Par3"));
	Tank_Part3CP->SetupAttachment(RootCP);

	ArrowCP = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Arrow"));
	ArrowCP->SetupAttachment(Tank_Part3CP);

	ShooterCP = CreateDefaultSubobject<USceneComponent>(TEXT("Shooter"));
	ShooterCP->SetupAttachment(ArrowCP);

	/* Path to Sprites*/
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Part3Obj(TEXT("PaperSprite'/Game/Assets/Sprites/Tank/tanks_turret1_Sprite.tanks_turret1_Sprite'"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> part4Obj(TEXT("PaperSprite'/Game/Assets/Sprites/Tank/tank_arrowFull_Sprite.tank_arrowFull_Sprite'"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Part1Obj(TEXT("PaperSprite'/Game/Assets/Sprites/Tank/tanks_tankGrey_body1_Sprite.tanks_tankGrey_body1_Sprite'"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Part2Obj(TEXT("PaperSprite'/Game/Assets/Sprites/Tank/tanks_tankTracks1_Sprite.tanks_tankTracks1_Sprite'"));


	if (Part3Obj.Succeeded() &&
		part4Obj.Succeeded() &&
		Part1Obj.Succeeded() &&
		Part2Obj.Succeeded())
	{
		Tank_Part1CP->SetSprite(Part1Obj.Object);
		Tank_Part2CP->SetSprite(Part2Obj.Object);
		Tank_Part3CP->SetSprite(Part3Obj.Object);
		ArrowCP->SetSprite(part4Obj.Object);
	}
	
	/* Configure components */
	Tank_Part1CP->SetRelativeLocation(FVector(-1.0f, 0.0f, 4.0f));
	Tank_Part2CP->SetRelativeLocation(FVector(-4.0f, 0.0f, -27.0f));
	Tank_Part3CP->SetRelativeLocation(FVector(3.0f, 0.0f, 33.0f));
	ArrowCP->SetRelativeLocation(FVector(57.0f, 0.0f, 1.21f));
	ShooterCP->SetRelativeLocation(FVector(150.0f, 0.0f, 0.0f));


	ExplosionRadius = 250.0f;
	LaunchVelocity = 1500.0f;
	ProjectileRadius = 20.0f;

}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TypeObj.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic)); 
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateCannon();
	PredictPath();
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Respond when our "Grow" key is pressed or released.
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::Fire);
	InputComponent->BindAxis("Distance", this, &ATankPawn::IncreaseSpeed);
}

void ATankPawn::IncreaseSpeed(float Val)
{

}

void ATankPawn::RotateCannon()
{
	/* Get Rotation Tank */
	float mouseX;
	float mouseY;
	FVector WorldLoc;
	FVector WorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY); 
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(WorldLoc, WorldDirection);
	FVector NewVector = WorldLoc - Tank_Part3CP->GetComponentLocation();
	NewVector.Y = 0;
	//Pitch Yaw Rol	
	FRotator RotTank = FRotator(FMath::Clamp(FRotationMatrix::MakeFromX(NewVector).Rotator().Pitch, -3.0f, 80.0f), 0.0f, 0.0f);
	Tank_Part3CP->SetRelativeRotation(RotTank);

}

void ATankPawn::PredictPath()
{

	FHitResult OutHit;
	FVector OutLastTraceDestination;
	TArray<AActor*> ActorsToIgnore;
	TArray<FVector> OutPathPositions;

	UGameplayStatics::Blueprint_PredictProjectilePath_ByObjectType(
		GetWorld(),
		OutHit,
		OutPathPositions,
		OutLastTraceDestination,
		ShooterCP->GetComponentLocation(),
		ShooterCP->GetForwardVector() * LaunchVelocity,
		true,
		ProjectileRadius,
		TypeObj,
		true,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		0.0f,
		8.0f,
		4.0f,
		0.0f
	);

	FColor ActualColor = (CurrentProject) ? FColor::Red : FColor::Blue;

	for (int32 i = 0; i < OutPathPositions.Num(); i++)
	{
		DrawDebugSphere(GetWorld(), OutPathPositions[i], ProjectileRadius, 12, ActualColor);
	}

	DrawDebugSphere(GetWorld(), OutPathPositions[OutPathPositions.Num() - 1], ExplosionRadius, 10, ActualColor);
}

void ATankPawn::Fire()
{
	FTransform NewT;
	NewT.SetLocation(ShooterCP->GetComponentLocation());
	NewT.SetRotation(FQuat(ShooterCP->GetComponentRotation()));
	NewT.SetScale3D(FVector(1.0f, 1.0f, 1.0f));


	CurrentProject = GetWorld()->SpawnActorDeferred<ABulletProjectile>(ABulletProjectile::StaticClass(), NewT);
	if (CurrentProject)
	{

		CurrentProject->ProjectileSpeed = LaunchVelocity;
		CurrentProject->ExplosionRadius = ExplosionRadius;
		CurrentProject->TypeObj = TypeObj;
		CurrentProject->ProjectileRadius = ProjectileRadius;

		UGameplayStatics::FinishSpawningActor(CurrentProject, NewT);
	}

}

