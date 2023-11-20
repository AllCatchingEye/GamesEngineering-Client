// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Cards/CardStackExtended.h"
#include "CardDeck.generated.h"

/**
 * The CardDeck class.
 * 
 * A CardDeck represents the initial deck of cards that are to be distributed.
 */
UCLASS(BlueprintType)
class SCHAFKOPF_API ACardDeck : public ACardStackExtended
{
	GENERATED_BODY()

public:
	ACardDeck();

	virtual int32 GetCardMaximum_Implementation() const final;

private:
	/** The maximum number of cards. */
	static const int32 CARD_COUNT_MAX = 32;

	// TODO: Implement card distribution/animation.
};
