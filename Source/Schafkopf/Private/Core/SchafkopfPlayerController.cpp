// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfPlayerController.h"
#include "Blueprint/UserWidget.h"

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

	// Create the HUD widget.
	if (this->WidgetClass && !this->WidgetInstance)
	{
		this->WidgetInstance = CreateWidget(this, this->WidgetClass);
		this->WidgetInstance->AddToViewport();
		this->bShowMouseCursor = true;
	}
}

//////////////////////////////////////////////////////////////////////////////////
// START - Widgets																//
//////////////////////////////////////////////////////////////////////////////////

void ASchafkopfPlayerController::ShowWidgetWantsToPlay()
{

}

void ASchafkopfPlayerController::ShowWidgetGameGroupSelect(const TArray<FString> Groups)
{

}

void ASchafkopfPlayerController::ShowWidgetGameTypeSelect(const TArray<FWSGameTypeWithSuit> Types)
{

}

//////////////////////////////////////////////////////////////////////////////////
// END - Widgets																//
//////////////////////////////////////////////////////////////////////////////////
