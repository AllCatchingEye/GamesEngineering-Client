// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SKPlayerController.h"

#include "Core/SKGameInstance.h"
#include "Core/WSMessage.h"
#include "Core/SKCharacter.h"
#include "Cards/Card.h"
#include "UI/GameHUD.h"
#include "UI/GameGroupSelectWidget.h"
#include "UI/GameTypeSelectWidget.h"
#include "UI/GameWinnerWidget.h"

#include "Blueprint/UserWidget.h"

ASKPlayerController::ASKPlayerController() : APlayerController()
{
	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true;
	this->bEnableMouseOverEvents = true;

	this->PosessedPawn = nullptr;

	this->WidgetInstance = nullptr;

	this->WidgetInstanceGameHUD = nullptr;
	this->WidgetInstanceWantsToPlay = nullptr;
	this->WidgetInstanceGameGroupSelect = nullptr;
	this->WidgetInstanceGameTypeSelect = nullptr;
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

	if (this->WidgetClassGameHUD && !this->WidgetInstanceGameHUD)
	{
		this->WidgetInstanceGameHUD = Cast<UGameHUD>(CreateWidget(this, this->WidgetClassGameHUD));
		//this->WidgetInstanceGameHUD->AddToViewport();
	}
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
	if (this->WidgetClassGameWinner && !this->WidgetInstanceGameWinner)
	{
		this->WidgetInstanceGameWinner = Cast<UGameWinnerWidget>(CreateWidget(this, this->WidgetClassGameWinner));
	}
}

ASKCharacter* ASKPlayerController::GetPosessedPawn()
{
	return this->PosessedPawn;
}

UFUNCTION(BlueprintCallable)
void ASKPlayerController::AddWidgetGameHUD()
{
	if (this->WidgetClassGameHUD && !this->WidgetInstanceGameHUD)
	{
		this->WidgetInstanceGameHUD = Cast<UGameHUD>(CreateWidget(this, this->WidgetClassGameHUD));
		this->WidgetInstanceGameHUD->AddToViewport();
	}
}

void ASKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	this->InputComponent->BindKey(EKeys::LeftMouseButton, EInputEvent::IE_Pressed, this, &ASKPlayerController::OnLeftMouseButtonPressed);
}

void ASKPlayerController::OnLeftMouseButtonPressed()
{
	FHitResult HitResult;
	this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

	AActor* HitActor = HitResult.GetActor();
	const bool bIsCard = HitActor && HitActor->IsA(ACard::StaticClass());
	if (HitResult.bBlockingHit && bIsCard)
	{
		ACard* Card = static_cast<ACard*>(HitActor);
		if (PosessedPawn->IsPlayableCard(Card))
		{
			static_cast<USKGameInstance*>(this->GetGameInstance())->SendCardPlay(PosessedPawn->GetPlayableCardIndex(Card));
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////
// START - Widgets																//
//////////////////////////////////////////////////////////////////////////////////

void ASKPlayerController::UpdateWidgetGameHUDMoney(int32 NewMoney)
{
	if (this->WidgetInstanceGameHUD)
	{
		this->WidgetInstanceGameHUD->UpdateMoney(NewMoney);
	}
}

void ASKPlayerController::UpdateWidgetGameHUDGameType(const FText NewGameType)
{
	if (this->WidgetInstanceGameHUD)
	{
		this->WidgetInstanceGameHUD->UpdateGameType(NewGameType);
	}
}

void ASKPlayerController::HideGameHUD()
{
	if (this->WidgetInstanceGameHUD)
	{
		this->WidgetInstanceGameHUD->HideHUD();
	}
}

void ASKPlayerController::ShowGameHUD()
{
	if (this->WidgetInstanceGameHUD)
	{
		this->WidgetInstanceGameHUD->ShowHUD();
	}
}

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

void ASKPlayerController::ShowWidgetGameWinner(bool isWinner, int32 Points)
{
	
	if (this->WidgetInstanceGameWinner)
	{
		this->WidgetInstanceGameWinner->AddToViewport();
		this->WidgetInstanceGameWinner->UpdateFields(isWinner, Points);
	}
}

//////////////////////////////////////////////////////////////////////////////////
// END - Widgets																//
//////////////////////////////////////////////////////////////////////////////////
