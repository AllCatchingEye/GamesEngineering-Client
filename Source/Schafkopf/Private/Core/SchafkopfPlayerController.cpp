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
	/*if (this->WidgetClass && !this->WidgetInstance)
	{
		this->WidgetInstance = CreateWidget(this, this->WidgetClass);
		this->WidgetInstance->AddToViewport();
		//this->bShowMouseCursor = true;
	}
	*/

	if (this->WidgetClassWantsToPlay && !this->WidgetInstanceWantsToPlay)
	{
		this->WidgetInstanceWantsToPlay = CreateWidget(this, this->WidgetClassWantsToPlay);
	}
	if (this->WidgetClassGameGroupSelect && !this->WidgetInstanceGameGroupSelect)
	{
		this->WidgetInstanceGameGroupSelect = Cast<UGameGroupSelectWidget>(CreateWidget(this, this->WidgetClassGameGroupSelect));
	}
	if (this->WidgetClassGameTypeSelect && !this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameTypeSelect = Cast<UGameTypeSelectWidget>(CreateWidget(this, this->WidgetClassGameTypeSelect));
	}
	if (this->WidgetClassCardSelect && !this->WidgetInstanceCardSelect)
	{
		this->WidgetInstanceCardSelect = Cast<UCardSelectWidget>(CreateWidget(this, this->WidgetClassCardSelect));
	}
	if (this->WidgetClassGameMoney && !this->WidgetInstanceGameMoney)
	{
		this->WidgetInstanceGameMoney = Cast<UGameMoney>(CreateWidget(this, this->WidgetClassGameMoney));
		this->ShowGameMoneyWidget();
	}
}

ASchafkopfCharacter* ASchafkopfPlayerController::GetPosessedPawn()
{
	return this->PosessedPawn;
}

//////////////////////////////////////////////////////////////////////////////////
// START - Widgets																//
//////////////////////////////////////////////////////////////////////////////////

void ASchafkopfPlayerController::ShowWidgetWantsToPlay()
{
	if (this->WidgetInstanceWantsToPlay)
	{
		this->WidgetInstanceWantsToPlay->AddToViewport();
	}
}

void ASchafkopfPlayerController::HideWidgetWantsToPlay()
{
	if (this->WidgetInstanceWantsToPlay)
	{
		this->WidgetInstanceWantsToPlay->RemoveFromViewport();
	}
}

void ASchafkopfPlayerController::ShowWidgetGameGroupSelect(const TArray<FString> Groups)
{
	if (this->WidgetInstanceGameGroupSelect)
	{
		this->WidgetInstanceGameGroupSelect->AddToViewport();
		// this->WidgetInstanceGameGroupSelect->UpdateFields(&Groups);
	}
}

void ASchafkopfPlayerController::HideWidgetGameGroupSelect()
{
	if (this->WidgetInstanceGameGroupSelect)
	{
		this->WidgetInstanceGameGroupSelect->RemoveFromViewport();
	}
}

void ASchafkopfPlayerController::ShowWidgetGameTypeSelect(const TArray<FWSGameTypeWithSuit> Types)
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameTypeSelect->AddToViewport();
		this->WidgetInstanceGameTypeSelect->UpdateFields(Types);
	}
}

void ASchafkopfPlayerController::HideWidgetGameTypeSelect()
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameTypeSelect->RemoveFromViewport();
	}
}

void ASchafkopfPlayerController::ShowWidgetCardSelect(const TArray<FWsCard> Cards)
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceCardSelect->AddToViewport();
		this->WidgetInstanceCardSelect->UpdateFields(Cards);
	}
}

void ASchafkopfPlayerController::ShowGameMoneyWidget()
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameMoney->AddToViewport();
	}
}

void ASchafkopfPlayerController::UpdateGameMoneyWidget()
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameMoney->UpdateMoneyUI();
	}
}

//////////////////////////////////////////////////////////////////////////////////
// END - Widgets																//
//////////////////////////////////////////////////////////////////////////////////
