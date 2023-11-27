// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SKPlayerController.h"

#include "Core/WSMessage.h"
#include "Core/SKCharacter.h"
#include "UI/GameGroupSelectWidget.h"
#include "UI/GameTypeSelectWidget.h"
#include "UI/CardSelectWidget.h"

#include "Blueprint/UserWidget.h"

ASKPlayerController::ASKPlayerController() : APlayerController()
{
	this->PosessedPawn = nullptr;

	this->WidgetInstance = nullptr;
	this->WidgetInstanceWantsToPlay = nullptr;
	this->WidgetInstanceGameGroupSelect = nullptr;
	this->WidgetInstanceGameTypeSelect = nullptr;
	this->WidgetInstanceCardSelect = nullptr;
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
