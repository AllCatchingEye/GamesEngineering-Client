// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfGameMode.h"
#include "Core/SchafkopfCharacter.h"
#include "Core/SchafkopfPlayerController.h"

ASchafkopfGameMode::ASchafkopfGameMode() : AGameModeBase()
{
	this->DefaultPawnClass = ASchafkopfCharacter::StaticClass();
	this->PlayerControllerClass = ASchafkopfPlayerController::StaticClass();
}
