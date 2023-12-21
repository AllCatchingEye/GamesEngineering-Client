// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cards/CardCollection.h"
#include "CardCollectionExtended.generated.h"

// Unreal Engine interfaces consist of two parts:
// 1. The class extending `UInterface`.
//    This class exists to make the interface visible to Unreal's reflection
//    system. It only contains the `GENERATED_BODY()` macro.
// 2. The actual interface class.
//	  This class holds the actual method definitions.

/**
 * The CardCollectionExtended interface.
 */
UINTERFACE(BlueprintType, Blueprintable, Category = "Cards")
class SCHAFKOPF_API UCardCollectionExtended : public UInterface
{
	GENERATED_BODY()
};

class SCHAFKOPF_API ICardCollectionExtended
{
	GENERATED_BODY()

public:
	/**
	 * Returns whether the card can be removed.
	 * 
	 * A card can be removed if all of the following are true:
	 * 1. `ToRemove` is not a `nullptr`.
	 * 2. `ToRemove` is in the collection.
	 *
	 * @return `true` if and only if the card can be removed.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool CanRemoveCard(ACard* ToRemove) const;

	/**
	 * Removes the specified card.
	 * 
	 * The card will be detached from this collection. The card's
	 * collision will not be reenabled.
	 * 
	 * A card can be removed if all of the following are true:
	 * 1. `ToRemove` is not a `nullptr`.
	 * 2. `ToRemove` is in the collection.
	 *
	 * @param ToRemove - The card to remove.
	 * @see CanRemoveCard(ACard*)
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	void RemoveCard(ACard* ToRemove);

	/**
	 * Removes the card specified by the suit and rank.
	 * 
	 * Does nothing if there is no card that matches the specified
	 * suit and rank.
	 * 
	 * @param Suit - The suit of the card.
	 * @param Rank - The rank of the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	void RemoveCardBySuitAndRank(ECardSuit Suit, ECardRank Rank);
};
