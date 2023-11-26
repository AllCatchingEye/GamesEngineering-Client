// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SKGameInstance.h"

#include "Core/WSMessage.h"
#include "Core/SKCharacter.h"
#include "Core/SKPlayerController.h"
#include "Cards/CardHand.h"
#include "Cards/CardTrick.h"

#include "IWebSocket.h"
#include "IWebSocketsManager.h"
#include "WebSocketsModule.h"
#include "JsonUtilities.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// START - GameInstance																			//
//////////////////////////////////////////////////////////////////////////////////////////////////

void USKGameInstance::Init()
{
	this->WebSocketConnect();

	// First we create the lobby type
	auto LobbyHost = FWSLobbyHost();
	LobbyHost.id = TEXT("lobby_host");
	LobbyHost.lobby_type = TEXT("single");
	auto Message = StructToJsonString(LobbyHost);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, Message);
	this->WebSocket->Send(Message);
}

void USKGameInstance::Shutdown()
{
	this->WebSocketDisconnect();
	Super::Shutdown();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - GameInstance																			//
//																								//
// START - WebSockets																			//
//////////////////////////////////////////////////////////////////////////////////////////////////

void USKGameInstance::WebSocketConnect()
{
	if (!FModuleManager::Get().IsModuleLoaded(this->WEB_SOCKET_MODULE))
	{
		FModuleManager::Get().LoadModule(this->WEB_SOCKET_MODULE);
	}

	//TODO: Change to `wss` protocol in Production.
	//The current protocol is unencrypted.
	this->WebSocket = FWebSocketsModule::Get().CreateWebSocket(this->WEB_SOCKET_ADDRESS, this->WEB_SOCKET_PROTOCOL);

	//Register event handlers.
	this->WebSocket->OnConnected().AddUFunction(this, FName("OnWebSocketConnected"));
	this->WebSocket->OnConnectionError().AddUFunction(this, FName("OnWebSocketConnectionError"));
	this->WebSocket->OnClosed().AddUFunction(this, FName("OnWebSocketClosed"));
	this->WebSocket->OnMessage().AddUFunction(this, FName("OnWebSocketMessageReceived"));

	this->WebSocket->Connect();
}

void USKGameInstance::WebSocketDisconnect()
{
	if (this->WebSocket && this->WebSocket->IsConnected())
	{
		this->WebSocket->Close();
	}
}

void USKGameInstance::OnWebSocketConnected()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, "Successfully connected.");
}

void USKGameInstance::OnWebSocketConnectionError(const FString& Error)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Red, Error);
}

void USKGameInstance::OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, bWasClean ? FColor::Green : FColor::Red, Reason);
}

void USKGameInstance::OnWebSocketMessageReceived(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::White, Message);

	FString MessageId = GetJsonMessageId(Message);

	if (MessageId == TEXT("GameStartUpdate")) { this->OnGameStartUpdate(Message); }
	else if (MessageId == TEXT("PlayDecisionUpdate")) {}
	else if (MessageId == TEXT("MoneyUpdate")) {}
	else if (MessageId == TEXT("PlayOrderUpdate")) { this->OnPlayOrderUpdate(Message); }
	else if (MessageId == TEXT("RoundResultUpdate")) { this->OnRoundResultUpdate(Message); }
	else if (MessageId == TEXT("GameEndUpdate")) { this->OnGameEndUpdate(Message); }

	// Queries
	else if (MessageId == TEXT("PlayerWantsToPlayQuery")) { this->OnPlayerWantsToPlayQuery(Message); }
	else if (MessageId == TEXT("PlayerChooseGameGroupQuery")) { this->OnPlayerSelectGameGroupQuery(Message); }
	else if (MessageId == TEXT("PlayerSelectGameTypeQuery")) { this->OnPlayerSelectGameTypeQuery(Message); }
	else if (MessageId == TEXT("PlayerPlayCardQuery")) { this->OnPlayerPlayCardQuery(Message); }

	// Query Updates
	// TODO: Missing PlayerWantsToPlayUpdate
	else if (MessageId == TEXT("GameGroupChosenUpdate")) { this->OnGameGroupSelectedUpdate(Message); }
	else if (MessageId == TEXT("GametypeDeterminedUpdate")) { this->OnGameTypeSelectedUpdate(Message); }
	else if (MessageId == TEXT("CardPlayedUpdate")) { this->OnCardPlayedUpdate(Message); }

	else
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE, 50.0f, FColor::Red,
			TEXT("Unknown message")
		);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - WebSockets																				//
//																								//
// START - Lobby																				//
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Lobby																					//
//																								//
// START - Ingame																				//
//////////////////////////////////////////////////////////////////////////////////////////////////

void USKGameInstance::OnGameStartUpdate(const FString& Message)
{
	// TODO: Initialize the game; possibly notify the server that this client is ready.
	
	// Load the ingame level.
	//UGameplayStatics::OpenLevel(this->GetWorld(), this->LEVEL_NAME_INGAME);

	const FWSMessageGameStartUpdate GameStartUpdate = JsonStringToStruct<FWSMessageGameStartUpdate>(Message);

	// Extract hand cards and player from event.
	TArray<FWSCard> HandCards = GameStartUpdate.hand;
	this->PlayerId = GameStartUpdate.player;

	// Fetch the player and ensure that it is not null.
	this->PlayerController = Cast<ASKPlayerController>(GetWorld()->GetFirstPlayerController());
	checkf(this->PlayerController != nullptr, TEXT("The player controller was null."));

	// Fetch the player's card hand and ensure that it is not null.
	ACardHand* CardHand = this->PlayerController->GetPosessedPawn()->GetCardHand();
	checkf(this->PlayerController != nullptr, TEXT("The player's card hand was null."));

	// Initialize the hand cards.
	ACard* CardActor = nullptr;
	UWorld* world = GetWorld();
	for (FWSCard card : HandCards)
	{
		// Create a new card actor.
		CardActor = world->SpawnActor<ACard>(ACard::StaticClass(), FVector(0, 0, 0), FRotator(0, 0, 0));
		ECardSuit suit = GetCardSuitFromString(card.suit);
		ECardRank rank = GetCardRankFromString(card.rank);
		CardActor->Update(suit, rank);

		// TODO: Remove debug messages.
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE, 50.0f, FColor::White,
			FString::Printf(TEXT("Card: %s %s"), *card.suit, *card.rank)
		);
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE, 50.0f, FColor::White,
			FString::Printf(TEXT("Card: %d %d"), (int)suit, (int)rank)
		);

		// Add the new card to hand.
		CardHand->AddCard_Implementation(CardActor);
	}

	// Spawn the initial card trick.
	this->CardTrick = GetWorld()->SpawnActor<ACardTrick>(ACardTrick::StaticClass());
}

void USKGameInstance::OnPlayOrderUpdate(const FString& Message)
{
	// TODO: Implement functionality.
	const FWSMessagePlayOrderUpdate Update = JsonStringToStruct<FWSMessagePlayOrderUpdate>(Message);
}

void USKGameInstance::OnRoundResultUpdate(const FString& Message)
{
	const FWSMessageRoundResultUpdate Update = JsonStringToStruct<FWSMessageRoundResultUpdate>(Message);

	// Before we destroy, move the cards to the origin, TODO: dirty fix
	this->CardTrick->MoveToOrigin();
	//Stack->Destroy();

	// Create a new empty card trick for the next round.
	this->CardTrick= GetWorld()->SpawnActor<ACardTrick>(ACardTrick::StaticClass());
}

void USKGameInstance::OnGameEndUpdate(const FString& Message)
{
	const FWSMessageGameEndUpdate Update = JsonStringToStruct<FWSMessageGameEndUpdate>(Message);
	
	// TODO: Extract winner / team and their points
	
	// TODO: Display winner / team with points received
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// START - Ingame - Queries																		//
//////////////////////////////////////////////////////////////////////////////////////////////////

void USKGameInstance::OnPlayerWantsToPlayQuery(const FString& Message)
{
	const FWSMessagePlayerWantsToPlayQuery Query = JsonStringToStruct<FWSMessagePlayerWantsToPlayQuery>(Message);

	// Ensure that the player is not null.
	checkf(this->PlayerController != nullptr, TEXT("The player controller was null."));
	this->PlayerController->ShowWidgetWantsToPlay();
}

void USKGameInstance::OnPlayerSelectGameGroupQuery(const FString& Message)
{
	const FWSMessagePlayerChooseGameGroupQuery Query = JsonStringToStruct<FWSMessagePlayerChooseGameGroupQuery>(Message);

	// Ensure that the player is not null.
	checkf(this->PlayerController != nullptr, TEXT("The player controller was null."));
	this->PlayerController->ShowWidgetGameGroupSelect(Query.available_groups);
}

void USKGameInstance::OnPlayerSelectGameTypeQuery(const FString& Message)
{
	const FWSMessagePlayerSelectGameTypeQuery Query = JsonStringToStruct<FWSMessagePlayerSelectGameTypeQuery>(Message);

	// Ensure that the player is not null.
	checkf(this->PlayerController != nullptr, TEXT("The player controller was null."));
	this->PlayerController->ShowWidgetGameTypeSelect(Query.choosable_gametypes);
}

void USKGameInstance::OnPlayerPlayCardQuery(const FString& Message)
{
	const FWSMessagePlayerPlayCardQuery Query = JsonStringToStruct<FWSMessagePlayerPlayCardQuery>(Message);

	// Ensure that the player is not null.
	checkf(this->PlayerController != nullptr, TEXT("The player controller was null."));
	this->PlayerController->ShowWidgetCardSelect(Query.playable_cards);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Ingame - Queries																		//
//																								//
// START - Ingame - Query Updates																//
//////////////////////////////////////////////////////////////////////////////////////////////////

void USKGameInstance::OnGameGroupSelectedUpdate(const FString& Message)
{
	// TODO: Implement functionality.
	const FWSMessageGameGroupChosenUpdate Update = JsonStringToStruct<FWSMessageGameGroupChosenUpdate>(Message);
}

void USKGameInstance::OnGameTypeSelectedUpdate(const FString& Message)
{
	// TODO: Implement functionality.
	const FWSMessageGametypeDeterminedUpdate Update = JsonStringToStruct<FWSMessageGametypeDeterminedUpdate>(Message);

	// TODO: Extract gametype from event

	// TODO: Do something with the gametype here
}

void USKGameInstance::OnCardPlayedUpdate(const FString& Message)
{
	const FWSMessageCardPlayedUpdate Update = JsonStringToStruct<FWSMessageCardPlayedUpdate>(Message);

	ECardSuit suit = GetCardSuitFromString(Update.card.suit);
	ECardRank rank = GetCardRankFromString(Update.card.rank);
	auto card = GetWorld()->SpawnActor<ACard>(ACard::StaticClass());
	card->Update(suit, rank);

	// Put the card onto the current trick.
	this->CardTrick->AddCard_Implementation(card);

	// Update the hand cards of the player.
	// TODO: Implement functionality for the cards of other "players".
	if (PlayerId.Equals(Update.player))
	{
		// Ensure that the player is not null.
		checkf(this->PlayerController != nullptr, TEXT("The player controller was null."));
		this->PlayerController->GetPosessedPawn()->GetCardHand()->RemoveCardByRankAndSuit_Implementation(rank, suit);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Ingame - Query Updates																	//
//																								//
// START - Ingame - Notify server																//
//////////////////////////////////////////////////////////////////////////////////////////////////

void USKGameInstance::SendWantsToPlay(const bool WantsToPlay)
{
	auto PlayerWantsToPlay = FWSMessagePlayerWantsToPlayAnswer();
	PlayerWantsToPlay.id = TEXT("PlayerWantsToPlayAnswer");
	PlayerWantsToPlay.decision = WantsToPlay;

	auto Message = StructToJsonString(PlayerWantsToPlay);
	WebSocket->Send(Message);
}


void USKGameInstance::SendGameGroupSelect(const int32 GameGroupIndex)
{
	auto PlayerChooseGameGroupResponse = FWSMessagePlayerChooseGameGroupAnswer();
	PlayerChooseGameGroupResponse.id = TEXT("PlayerChooseGameGroupAnswer");
	PlayerChooseGameGroupResponse.gamegroup_index = GameGroupIndex;

	auto Message = StructToJsonString(PlayerChooseGameGroupResponse);
	WebSocket->Send(Message);
}

void USKGameInstance::SendGameTypeSelect(const int32 GameTypeIndex)
{
	auto PlayerSelectGameTypeResponse = FWSMessagePlayerSelectGameTypeAnswer();
	PlayerSelectGameTypeResponse.id = TEXT("PlayerSelectGameTypeAnswer");
	PlayerSelectGameTypeResponse.gametype_index = GameTypeIndex;

	auto Message = StructToJsonString(PlayerSelectGameTypeResponse);
	WebSocket->Send(Message);
}

void USKGameInstance::SendCardPlay(const int32 CardIndex)
{
	auto PlayerPlayCardResponse = FWSMessagePlayerPlayCardAnswer();
	PlayerPlayCardResponse.id = TEXT("PlayerPlayCardAnswer");
	PlayerPlayCardResponse.card_index = CardIndex;

	auto Message = StructToJsonString(PlayerPlayCardResponse);
	WebSocket->Send(Message);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Ingame - Notify server																	//
// END - Ingame																					//
//////////////////////////////////////////////////////////////////////////////////////////////////