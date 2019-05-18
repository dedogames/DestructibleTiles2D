// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosionActor.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbook.h"

// Sets default values
AExplosionActor::AExplosionActor()
{
	ExplosionFlipbookCP = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Kabum"));
	RootComponent = ExplosionFlipbookCP;
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> ExplosionObj(TEXT("PaperFlipbook'/Game/Assets/Flipbooks/Explosion_Flipbook.Explosion_Flipbook'"));
	if (ExplosionObj.Succeeded())
		ExplosionFlipbookCP->SetFlipbook(ExplosionObj.Object);

}

// Called when the game starts or when spawned
void AExplosionActor::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, FTimerDelegate::CreateLambda(
		[this]
	{
		Destroy();
	}), ExplosionFlipbookCP->GetFlipbookLength()*0.9, false);
}
 
