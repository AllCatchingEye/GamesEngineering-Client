// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfGameInstance.h"

#include "JsonUtilities.h"

const char* USchafkopfGameInstance::WEB_SOCKET_MODULE = "WebSockets";
const char* USchafkopfGameInstance::WEB_SOCKET_ADDRESS = "ws://localhost:8765";
const char* USchafkopfGameInstance::WEB_SOCKET_PROTOCOL = "ws";

/* 
* Serialize a WebSocket message struct to a JSON string.
*/
template<typename T = FWsMessage>
FString StructToJsonString(const T& Struct)
{
	FString OutputString;
	auto result = FJsonObjectConverter::UStructToJsonObjectString(Struct, OutputString, 0, 0, 0);
	if (!result)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::Red, TEXT("Failed to serialize struct to JSON string."));
	}
	return OutputString;
}

/*
* Returns the message id from a JSON string.
*/
FString GetJsonMessageId(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	FString MessageId;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		JsonObject->TryGetStringField(TEXT("id"), MessageId);
	}

	if (MessageId.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::Red, TEXT("Failed to get message id from JSON string."));
	}

	return MessageId;
}


/* 
* Deserialize a JSON string to a WebSocket message struct.
*/
template<typename T = FWsMessage>
T JsonStringToStruct(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	T OutputStruct;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		auto result = FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), T::StaticStruct(), &OutputStruct, 0, 0);

		if (!result)
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::Red, TEXT("Failed to deserialize JSON string to struct."));
		}
	}

	return OutputStruct;
}


void USchafkopfGameInstance::Init()
{
	WebSocketConnect();

	// First we create the lobby type
	auto LobbyHost = FWsLobbyHost();
	LobbyHost.id = TEXT("lobby_host");
	LobbyHost.lobby_type = TEXT("single");
	auto Message = StructToJsonString(LobbyHost);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, Message);
	WebSocket->Send(Message);
}

void USchafkopfGameInstance::Shutdown()
{
	WebSocketDisconnect();
	Super::Shutdown();
}

void USchafkopfGameInstance::WebSocketConnect()
{
	if (!FModuleManager::Get().IsModuleLoaded(WEB_SOCKET_MODULE))
	{
		FModuleManager::Get().LoadModule(WEB_SOCKET_MODULE);
	}

	//TODO: Change to `wss` protocol in Production.
	//The current protocol is unencrypted.
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(WEB_SOCKET_ADDRESS, WEB_SOCKET_PROTOCOL);

	//Register event handlers.
	WebSocket->OnConnected().AddUFunction(this, FName("OnWebSocketConnected"));
	WebSocket->OnConnectionError().AddUFunction(this, FName("OnWebSocketConnectionError"));
	WebSocket->OnClosed().AddUFunction(this, FName("OnWebSocketClosed"));
	WebSocket->OnMessage().AddUFunction(this, FName("OnWebSocketMessageReceived"));

	WebSocket->Connect();
}

void USchafkopfGameInstance::WebSocketDisconnect()
{
	if (WebSocket && WebSocket->IsConnected())
	{
		WebSocket->Close();
	}
}

void USchafkopfGameInstance::OnWebSocketConnected()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, "Successfully connected.");
}

void USchafkopfGameInstance::OnWebSocketConnectionError(const FString& Error)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.0f, FColor::Red, Error);
}

void USchafkopfGameInstance::OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, bWasClean ? FColor::Green : FColor::Red, Reason);
}

void USchafkopfGameInstance::OnWebSocketMessageReceived(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::White, Message);

	auto MessageId = GetJsonMessageId(Message);

	if (MessageId == TEXT("GameStartUpdate"))
	{
		auto GameStartUpdate = JsonStringToStruct<FWsMessageGameStartUpdate>(Message);

		// Extract cards and player from event
		auto hand = GameStartUpdate.hand;
		auto players = GameStartUpdate.player;

		// Display hand
	} 
	else if (MessageId == TEXT("PlayDecisionUpdate"))
	{
		auto PlayDecisionUpdate = JsonStringToStruct<FWsMessagePlayDecisionUpdate>(Message);

		// Extract decisions from event

		// Display decisions

		// Ask player which decision he wants to select
	} 
	else if (MessageId == TEXT("GametypeDeterminedUpdate"))
	{
		auto PlayUpdate = JsonStringToStruct<FWsMessageGametypeDeterminedUpdate>(Message);

		// Extract gametype from event

		// Do something with the gametype here
	}
	else if (MessageId == TEXT("CardPlayedUpdate"))
	{
		auto GameEndUpdate = JsonStringToStruct<FWsMessageCardPlayedUpdate>(Message);

		// Put Card on stack

		// Update hand
	}
	else if (MessageId == TEXT("RoundResultUpdate"))
	{
		auto GameEndUpdate = JsonStringToStruct<FWsMessageRoundResultUpdate>(Message);

		// Extract winner and points of the round

		// Display winner with points received
	}
	else if (MessageId == TEXT("GameEndUpdate"))
	{
		auto GameEndUpdate = JsonStringToStruct<FWsMessageGameEndUpdate>(Message);

		// Extract winner / team and their points

		// Display winner / team with points received
	} // TODO FWsMessageAnnouncePlayPartyUpdate
	else if (MessageId == TEXT("GameGroupChosenUpdate"))
	{
		auto AnnouncePlayPartyUpdate = JsonStringToStruct<FWsMessageGameGroupChosenUpdate>(Message);
	}
	else if (MessageId == TEXT("MoneyUpdate")) 
	{
		auto MoneyUpdate = JsonStringToStruct<FWsMessageMoneyUpdate>(Message);
	}
	else if (MessageId == TEXT("PlayOrderUpdate"))
	{
		auto PlayOrderUpdate = JsonStringToStruct<FWsMessagePlayOrderUpdate>(Message);
	}
	// --- Queries - Action is required ---
	else if (MessageId == TEXT("PlayerWantsToPlayQuery"))
	{
		auto PlayerWantsToPlayQuery = JsonStringToStruct<FWsMessagePlayerWantsToPlayQuery>(Message);
		// randomly choose yes or no
		auto PlayerWantsToPlayResponse = FWsMessagePlayerWantsToPlayAnswer();
		PlayerWantsToPlayResponse.id = TEXT("PlayerWantsToPlayAnswer");
		PlayerWantsToPlayResponse.decision = FMath::RandBool();

		auto Message = StructToJsonString(PlayerWantsToPlayResponse);
		WebSocket->Send(Message);
	}
	else if (MessageId == TEXT("PlayerSelectGameTypeQuery"))
	{
		auto PlayerSelectGameTypeQuery = JsonStringToStruct<FWsMessagePlayerSelectGameTypeQuery>(Message);

		// randomly choose one of the game types
		auto PlayerSelectGameTypeResponse = FWsMessagePlayerSelectGameTypeAnswer();
		PlayerSelectGameTypeResponse.id = TEXT("PlayerSelectGameTypeAnswer");
		auto index = FMath::RandRange(0, PlayerSelectGameTypeQuery.choosable_gametypes.Num() - 1);
		PlayerSelectGameTypeResponse.gametype_index = index;

		auto Message = StructToJsonString(PlayerSelectGameTypeResponse);
		WebSocket->Send(Message);
	}
	else if (MessageId == TEXT("PlayerChooseGameGroupQuery"))
	{
		auto PlayerChooseGameGroupQuery = JsonStringToStruct<FWsMessagePlayerChooseGameGroupQuery>(Message);

		// randomly choose one of the game groups
		auto PlayerChooseGameGroupResponse = FWsMessagePlayerChooseGameGroupAnswer();
		PlayerChooseGameGroupResponse.id = TEXT("PlayerChooseGameGroupAnswer");
		auto index = FMath::RandRange(0, PlayerChooseGameGroupQuery.available_groups.Num() - 1);
		PlayerChooseGameGroupResponse.gamegroup_index = index;

		auto Message = StructToJsonString(PlayerChooseGameGroupResponse);
		WebSocket->Send(Message);
	}
	else if (MessageId == TEXT("PlayerPlayCardQuery")) {
		auto PlayerPlayCardQuery = JsonStringToStruct<FWsMessagePlayerPlayCardQuery>(Message);

		// randomly choose one of the cards
		auto PlayerPlayCardResponse = FWsMessagePlayerPlayCardAnswer();
		PlayerPlayCardResponse.id = TEXT("PlayerPlayCardAnswer");
		auto index = FMath::RandRange(0, PlayerPlayCardQuery.playable_cards.Num() - 1);
		PlayerPlayCardResponse.card_index = index;

		auto Message = StructToJsonString(PlayerPlayCardResponse);
		WebSocket->Send(Message);
	}
	else {
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::Red, TEXT("Unknown message"));
	}
}

