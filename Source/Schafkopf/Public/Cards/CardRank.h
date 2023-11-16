// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardRank.generated.h"

/**
 * The CardRank enum.
 * 
 * Provides a list of all available ranks, that a card may have.
 * 
 * The value of `NONE` is used exclusively in cases where a client
 * should not be aware of the actual card. For example: Any cards
 * that are in the hand of another player should not be known to
 * the current player. The server obviously always knows about all
 * cards, and thus does not need the `NONE` value.
 */
UENUM(BlueprintType)
enum class ECardRank : uint8
{
	NONE = 0		UMETA(DisplayName = "NONE"),
	SIEBEN = 1		UMETA(DisplayName = "SIEBEN"),
	ACHT = 2		UMETA(DisplayName = "ACHT"),
	NEUN = 3		UMETA(DisplayName = "NEUN"),
	UNTER = 4		UMETA(DisplayName = "UNTER"),
	OBER = 5		UMETA(DisplayName = "OBER"),
	KOENIG = 6		UMETA(DisplayName = "KOENIG"),
	ZEHN = 7		UMETA(DisplayName = "ZEHN"),
	ASS = 8			UMETA(DisplayName = "ASS")
};

ENUM_RANGE_BY_FIRST_AND_LAST(ECardRank, ECardRank::SIEBEN, ECardRank::ASS);
