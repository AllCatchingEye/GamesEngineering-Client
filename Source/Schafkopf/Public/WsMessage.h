// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WsMessage.generated.h"

USTRUCT()
struct SCHAFKOPF_API FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString id;
};

USTRUCT()
struct SCHAFKOPF_API FWsLobbyHost : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString lobby_type;
};


USTRUCT()
struct SCHAFKOPF_API FWsCard
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString suit; // TODO: Enum value?

	UPROPERTY()
	FString rank; // TODO: Enum value?
};

USTRUCT()
struct SCHAFKOPF_API FWsMessageGameStartUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString player;

	UPROPERTY()
	TArray<FWsCard> hand;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayDecisionUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString player;

	UPROPERTY()
	bool wants_to_play;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessageGametypeDeterminedUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString player; // TODO: This can be None?

	UPROPERTY()
	FString gametype; // TODO: How to do enum values?

	UPROPERTY()
	FString suit; // TODO: Optional

	//UPROPERTY()
	//TArray<TArray<FString>> parties; // TODO: Optional, and typing?
};

USTRUCT()
struct SCHAFKOPF_API FWsMessageCardPlayedUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString player;

	UPROPERTY()
	FWsCard card;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessageRoundResultUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString round_winner;

	UPROPERTY()
	int points;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessageGameEndUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FString> winner;

	//UPROPERTY()
	//TArray<TArray<FString>> play_party; // TODO: Is this needed?

	UPROPERTY()
	TArray<int> points;
};

//USTRUCT()
//struct SCHAFKOPF_API FWsMessageAnnouncePlayPartyUpdate : public FWsMessage
//{
//	GENERATED_BODY()

//public:
//	//UPROPERTY()
//	//TArray<TArray<FString>> parties; // TODO: Typing
//};

USTRUCT()
struct SCHAFKOPF_API FWsMessageGameGroupChosenUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString player;

	UPROPERTY()
	TArray<FString> game_groups;
};

USTRUCT()
struct SCHAFKOPF_API FWsMoney
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int cents;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessageMoneyUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString player;

	UPROPERTY()
	FWsMoney money;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayOrderUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FString> order;
};

// --- Queries & Answers - Action is required ---

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerWantsToPlayQuery : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString current_lowest_gamegroup;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerWantsToPlayAnswer : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool decision;
};


USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerSelectGameTypeQuery : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FString> choosable_gametypes;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerSelectGameTypeAnswer : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int gametype_index;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerChooseGameGroupQuery : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FString> available_groups;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerChooseGameGroupAnswer : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int gamegroup_index;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerPlayCardQuery : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FWsCard> playable_cards;
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayerPlayCardAnswer : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int card_index;
};
