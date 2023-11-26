// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfGameMode.h"
#include "Core/SKCharacter.h"
#include "Core/SKPlayerController.h"

ASchafkopfGameMode::ASchafkopfGameMode() : AGameModeBase()
{
	this->DefaultPawnClass = ASKCharacter::StaticClass();
	this->PlayerControllerClass = ASKPlayerController::StaticClass();
}
