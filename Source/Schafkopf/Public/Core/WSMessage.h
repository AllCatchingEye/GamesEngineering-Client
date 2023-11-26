// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "JsonUtilities.h"

#include "WSMessage.generated.h"

/**
 * The base WebSocketMessage.
 * Only contains an ID that every message needs.
 */
USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessage
{
	GENERATED_BODY()

public:
	/** The ID of the message. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString id;
};

/**
 * The base websocket message for everything that is player related.
 * Contains the message and player ID.
 */
USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerRelated : public FWSMessage
{
	GENERATED_BODY()

public:
	/** The ID of the player. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString player;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// START - Lobby																				//
//////////////////////////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSLobbyHost : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString lobby_type;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Lobby																					//
//																								//
// START - Ingame																				//
//////////////////////////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSCard
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString suit; // TODO: Enum value?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString rank; // TODO: Enum value?
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessageGameStartUpdate : public FWSMessagePlayerRelated
{
	GENERATED_BODY()

public:
	/** The hand cards of the player. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<FWSCard> hand;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayDecisionUpdate : public FWSMessagePlayerRelated
{
	GENERATED_BODY()

public:
	/** Determines whether the player wants to play. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	bool wants_to_play;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessageGametypeDeterminedUpdate : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString player; // TODO: This can be None?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString gametype; // TODO: How to do enum values?

	UPROPERTY()
	FString suit; // TODO: Optional

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	//TArray<TArray<FString>> parties; // TODO: Optional, and typing?
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessageCardPlayedUpdate : public FWSMessagePlayerRelated
{
	GENERATED_BODY()

public:
	/** The card that the player played. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FWSCard card;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessageRoundResultUpdate : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString round_winner;// TODO: Rename to `player` for better unity.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	int points;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessageGameEndUpdate : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<FString> winner;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	//TArray<TArray<FString>> play_party; // TODO: Is this needed?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<int> points;
};

//USTRUCT()
//struct SCHAFKOPF_API FWSMessageAnnouncePlayPartyUpdate : public FWSMessage
//{
//	GENERATED_BODY()

//public:
//	//UPROPERTY()
//	//TArray<TArray<FString>> parties; // TODO: Typing
//};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessageGameGroupChosenUpdate : public FWSMessagePlayerRelated
{
	GENERATED_BODY()

public:
	/** The game groups that are available. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<FString> game_groups;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMoney
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	int cents;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessageMoneyUpdate : public FWSMessagePlayerRelated
{
	GENERATED_BODY()

public:
	/** The new amount of money that the player posesses. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FWSMoney money;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayOrderUpdate : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<FString> order;
};

// --- Queries & Answers - Action is required ---

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerWantsToPlayQuery : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString current_lowest_gamegroup;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerWantsToPlayAnswer : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	bool decision;
};


USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSGameTypeWithSuit
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Schafkopf")
	FString gametype;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	FString suit;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerSelectGameTypeQuery : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<FWSGameTypeWithSuit> choosable_gametypes;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerSelectGameTypeAnswer : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	int gametype_index;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerChooseGameGroupQuery : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<FString> available_groups;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerChooseGameGroupAnswer : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	int gamegroup_index;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerPlayCardQuery : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	TArray<FWSCard> playable_cards;
};

USTRUCT(BlueprintType)
struct SCHAFKOPF_API FWSMessagePlayerPlayCardAnswer : public FWSMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schafkopf")
	int card_index;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Ingame																					//
//																								//
// START - Helper functions																		//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Returns the message ID from a websocket message JSON string.
 *
 * @param JsonString - The websocket message JSON string.
 * @return The message ID.
 */
FString GetJsonMessageId(const FString& JsonString);

/**
 * Serialize a websocket message struct to a JSON string.
 * 
 * @param Struct - The websocket message struct to serialize.
 * @return The JSON string.
 */
template<typename T = FWSMessage>
FString StructToJsonString(const T& Struct)
{
	FString OutputString;
	auto result = FJsonObjectConverter::UStructToJsonObjectString(Struct, OutputString, 0, 0, 0);
	if (!result)
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE, 50.0f, FColor::Red,
			TEXT("Failed to serialize struct to JSON string.")
		);
	}
	return OutputString;
}

/**
 * Deserialize a JSON string to a websocket message struct.
 * 
 * @param JsonString - The JSON string to deserialize.
 * @return The websocket message struct.
 */
template<typename T = FWSMessage>
T JsonStringToStruct(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	T OutputStruct;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		auto result = FJsonObjectConverter::JsonObjectToUStruct(
			JsonObject.ToSharedRef(), T::StaticStruct(),
			&OutputStruct, 0, 0
		);

		if (!result)
		{
			GEngine->AddOnScreenDebugMessage(
				INDEX_NONE, 50.0f, FColor::Red,
				TEXT("Failed to deserialize JSON string to struct.")
			);
		}
	}

	return OutputStruct;
}

// Forward declare the card suit and rank enums:
enum class ECardSuit : uint8;
enum class ECardRank : uint8;

/**
 * Parses a string to an ECardSuit enum.
 * 
 * @param SuitString - The card suit as string.
 * @return The corresponding ECardSuit enum.
 */
ECardSuit GetCardSuitFromString(const FString& SuitString);

/**
 * Parses a string to an ECardRank enum.
 * 
 * @param RankString - The card rank as string.
 * @return The corresponding ECardRank enum.
 */
ECardRank GetCardRankFromString(const FString& RankString);

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Helper functions																		//
//////////////////////////////////////////////////////////////////////////////////////////////////
