// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfPlayerController.h"

ASchafkopfPlayerController::ASchafkopfPlayerController() : APlayerController()
{
	this->PosessedPawn = nullptr;

	this->WidgetInstance = nullptr;
}

void ASchafkopfPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->PosessedPawn = Cast<ASchafkopfCharacter>(this->GetPawn());

	this->SetInputMode(FInputModeGameAndUI());
}
