// Fill out your copyright notice in the Description page of Project Settings.


#include "Maps/MainMenuLevel.h"

AMainMenuLevel::AMainMenuLevel() : ALevelScriptActor()
{
	this->GameInstance = nullptr;
}

void AMainMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	this->GameInstance = (USchafkopfGameInstance*) GetGameInstance();
}
