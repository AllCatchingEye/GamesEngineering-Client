// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Cards/CardStack.h"
#include "CardTrick.generated.h"

/**
 * The CardTrick class.
 * 
 * A CardTrick represents a trick of cards that a player has made.
 * Each trick consists of exactly four cards.
 * 
 * A new CardTrick is spawned each round. The played cards will be added to this
 * CarTrick one after another. Once the server has determined which player has
 * made the trick, the owner will be set.
 */
UCLASS(BlueprintType)
class SCHAFKOPF_API ACardTrick : public ACardStack
{
	GENERATED_BODY()

public:
	ACardTrick();

	virtual int32 GetCardMaximum_Implementation() const final;

	virtual void AddCard_Implementation(ACard* ToAdd) final;

	UFUNCTION(BlueprintCallable, Category = "Cards")
	static void DisappearCards(ACardTrick* CardTrick);

private:
	/** The maximum number of cards. */
	static const int32 CARD_COUNT_MAX = 4;

	/** Rearranges the hand cards along the spline. */
	void RearrangeCards();
};

