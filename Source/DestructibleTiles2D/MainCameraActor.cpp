// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraActor.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMainCameraActor::AMainCameraActor()
{

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCP"));

	MainCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	MainCamera->SetOrthoWidth(4800.0f);
	MainCamera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


}
 