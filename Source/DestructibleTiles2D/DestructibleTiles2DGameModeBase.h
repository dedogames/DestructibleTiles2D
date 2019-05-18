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
#include "GameFramework/GameModeBase.h"
#include "DestructibleTiles2DGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DESTRUCTIBLETILES2D_API ADestructibleTiles2DGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ADestructibleTiles2DGameModeBase();
	virtual void BeginPlay() override;
 
	
};
