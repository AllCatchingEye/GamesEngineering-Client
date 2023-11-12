// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

/**
 * The CardSuit enum.
 * 
 * Provides a list of all available suits, that a card may have.
 */
UENUM(BlueprintType)
enum class ECardSuit : uint8
{
	EICHEL = 0		UMETA(DispalyName = "EICHEL"),
	GRAS = 1		UMETA(DispalyName = "GRAS"),
	HERZ = 2		UMETA(DispalyName = "HERZ"),
	SCHELLEN = 3	UMETA(DispalyName = "SCHELLEN")
};

/**
 * The CardRank enum.
 * 
 * Provides a list of all available ranks, that a card may have.
 */
UENUM(BlueprintType)
enum class ECardRank : uint8
{
	SIEBEN = 0		UMETA(DisplayName = "SIEBEN"),
	ACHT = 1		UMETA(DisplayName = "ACHT"),
	NEUN = 2		UMETA(DisplayName = "NEUN"),
	UNTER = 3		UMETA(DisplayName = "UNTER"),
	OBER = 4		UMETA(DisplayName = "OBER"),
	KOENIG = 5		UMETA(DisplayName = "KOENIG"),
	ZEHN = 6		UMETA(DisplayName = "ZEHN"),
	ASS = 7			UMETA(DisplayName = "ASS")
};

/**
 * The card class.
 */
UCLASS(BlueprintType)
class SCHAFKOPF_API UCard : public UObject
{
	GENERATED_BODY()
	
private:
	/** The suit of the card. */
	ECardSuit Suit;
	/** The rank of the card. */
	ECardRank Rank;

public:
	/**
	 * Returns the suit of the card.
	 * 
	 * @return The suit of the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECardSuit getSuit() const;
	/**
	 * Returns the rank of the card.
	 *
	 * @return The rank of the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECardRank getRank() const;
};
