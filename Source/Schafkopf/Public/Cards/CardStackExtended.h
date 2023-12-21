// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Cards/CardCollectionExtended.h"
#include "Cards/CardStack.h"
#include "CardStackExtended.generated.h"

/**
 * The abstract CardStackExtended class.
 * 
 * A CardStackExtended is a collection of cards. This basic implementation allows
 * both the adding and removing of cards. The number of cards a CardStack can hold
 * is determined by the specific child class.
 */
UCLASS(Abstract, BlueprintType)
class SCHAFKOPF_API ACardStackExtended : public ACardStack, public ICardCollectionExtended
{
	GENERATED_BODY()

public:
	ACardStackExtended();

	virtual int32 GetCardMaximum_Implementation() const PURE_VIRTUAL(ACardStack::GetCardMaximum, return -1;);

	virtual bool CanRemoveCard_Implementation(ACard* ToRemove) const final;

	virtual void RemoveCard_Implementation(ACard* ToRemove) override;

	virtual void RemoveCardBySuitAndRank_Implementation(ECardSuit Suit, ECardRank Rank) override;
};
