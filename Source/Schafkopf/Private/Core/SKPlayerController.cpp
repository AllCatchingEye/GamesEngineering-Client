// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SKPlayerController.h"

#include "Core/WSMessage.h"
#include "Core/SKCharacter.h"
#include "UI/GameGroupSelectWidget.h"
#include "UI/GameTypeSelectWidget.h"
#include "UI/CardSelectWidget.h"
#include "UI/GameMoney.h"
#include "UI/GameWinnerWidget.h"

#include "Blueprint/UserWidget.h"

ASKPlayerController::ASKPlayerController() : APlayerController()
{
	this->PosessedPawn = nullptr;

	this->WidgetInstance = nullptr;
	this->WidgetInstanceWantsToPlay = nullptr;
	this->WidgetInstanceGameGroupSelect = nullptr;
	this->WidgetInstanceGameTypeSelect = nullptr;
	this->WidgetInstanceCardSelect = nullptr;
	this->WidgetInstanceGameMoney= nullptr;
	this->WidgetInstanceGameWinner = nullptr;
}

void ASKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->PosessedPawn = Cast<ASKCharacter>(this->GetPawn());

	this->SetInputMode(FInputModeGameAndUI());

	// TODO: Create the HUD widget.
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
	if (this->WidgetClassGameWinner && !this->WidgetInstanceGameWinner)
	{
		this->WidgetInstanceGameWinner = Cast<UGameWinnerWidget>(CreateWidget(this, this->WidgetClassGameWinner));
	}
}

ASKCharacter* ASKPlayerController::GetPosessedPawn()
{
	return this->PosessedPawn;
}

//////////////////////////////////////////////////////////////////////////////////
// START - Widgets																//
//////////////////////////////////////////////////////////////////////////////////

void ASKPlayerController::ShowWidgetWantsToPlay()
{
	if (this->WidgetInstanceWantsToPlay)
	{
		this->WidgetInstanceWantsToPlay->AddToViewport();
	}
}

void ASKPlayerController::ShowWidgetGameGroupSelect(const TArray<FString> Groups)
{
	if (this->WidgetInstanceGameGroupSelect)
	{
		this->WidgetInstanceGameGroupSelect->AddToViewport();
		this->WidgetInstanceGameGroupSelect->UpdateFields(Groups);
	}
}

void ASKPlayerController::ShowWidgetGameTypeSelect(const TArray<FWSGameTypeWithSuit> Types)
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameTypeSelect->AddToViewport();
		this->WidgetInstanceGameTypeSelect->UpdateFields(Types);
	}
}

void ASKPlayerController::ShowWidgetCardSelect(const TArray<FWSCard> Cards)
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceCardSelect->AddToViewport();
		this->WidgetInstanceCardSelect->UpdateFields(Cards);
	}
}

void ASKPlayerController::ShowGameMoneyWidget()
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameMoney->AddToViewport();
	}
}

void ASKPlayerController::UpdateGameMoneyWidget(int money)
{
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameMoney->UpdateMoneyUI(money);
	}
}

void ASKPlayerController::ShowWidgetGameWinner(const TArray<FString> Winners, int Points)
{
	
	if (this->WidgetInstanceGameTypeSelect)
	{
		this->WidgetInstanceGameWinner->AddToViewport();
		this->WidgetInstanceGameWinner->UpdateFields(Winners, Points);
	}
}

//////////////////////////////////////////////////////////////////////////////////
// END - Widgets																//
//////////////////////////////////////////////////////////////////////////////////
