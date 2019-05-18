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


#include "DestructibleTiles2DGameModeBase.h"
#include "MainCameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "MPlayerController.h"
#include "TankPawn.h"
 
 


ADestructibleTiles2DGameModeBase::ADestructibleTiles2DGameModeBase()
{
 
	DefaultPawnClass	  = ATankPawn::StaticClass();
	PlayerControllerClass = AMPlayerController::StaticClass();
}

void ADestructibleTiles2DGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	AMainCameraActor *MainCamera = GetWorld()->SpawnActor<AMainCameraActor>(AMainCameraActor::StaticClass());
	MainCamera->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(MainCamera); 

}
