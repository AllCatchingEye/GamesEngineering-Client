// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"

#include "Cards/CardStackExtended.h"
#include "CardHand.generated.h"

/**
 * The CardHand class.
 * 
 * A CardHand represents the hand cards of a player. A hand may consist of up to
 * eight cards. During the course of the game, each round a card is played and
 * thus removed from the hand.
 */
UCLASS(BlueprintType)
class SCHAFKOPF_API ACardHand : public ACardStackExtended
{
	GENERATED_BODY()

public:
	ACardHand();

	virtual int32 GetCardMaximum_Implementation() const override;

	virtual void AddCard_Implementation(ACard* ToAdd) final;

	virtual void RemoveCard_Implementation(ACard* ToRemove) final;

	void HighlightCards(TArray<struct FWSCard>* ToHighlight);

private:
	/** The maximum number of cards. */
	static const int32 CARD_COUNT_MAX = 8;

	/** The spline along which the cards will be arranged. */
	USplineComponent* CardSpline;

	/** Rearranges the hand cards along the spline. */
	void RearrangeCards();
};
