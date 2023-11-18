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
	FString suit;

	UPROPERTY()
	FString rank;
};

USTRUCT()
struct SCHAFKOPF_API FWsGameStartUpdate : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString player;

	UPROPERTY()
	TArray<FWsCard> hand;	
};

USTRUCT()
struct SCHAFKOPF_API FWsMessagePlayDecision : public FWsMessage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString PlayerId;

	UPROPERTY()
	bool WantsToPlay;
};
