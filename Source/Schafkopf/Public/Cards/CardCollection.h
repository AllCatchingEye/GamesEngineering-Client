// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cards/Card.h"
#include "CardCollection.generated.h"

// Unreal Engine interfaces consist of two parts:
// 1. The class extending `UInterface`.
//    This class exists to make the interface visible to Unreal's reflection
//    system. It only contains the `GENERATED_BODY()` macro.
// 2. The actual interface class.
//	  This class holds the actual method definitions.

/**
 * The CardCollection interface.
 */
UINTERFACE(BlueprintType, Blueprintable, Category = "Cards")
class SCHAFKOPF_API UCardCollection : public UInterface
{
	GENERATED_BODY()
};

class SCHAFKOPF_API ICardCollection
{
	GENERATED_BODY()

public:
	/**
	 * Returns the maximum number of cards.
	 *
	 * @return The maximum number of cards.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	int32 GetCardMaximum() const;

	/**
	 * Returns the number of cards.
	 *
	 * @return The number of cards.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	int32 GetCardCount() const;

	/**
	 * Returns whether the collection is empty.
	 *
	 * @return `true` if and only if the collection is empty.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool IsEmpty() const;

	/**
	 * Returns whether the collection is full.
	 *
	 * @return `true` if and only if the collection is full.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool IsFull() const;

	/**
	 * Returns whether the collection contains the card.
	 * 
	 * @param ToQuery - The card to check for.
	 * @return `true` if and only if the collection contains the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool ContainsCard(ACard* ToQuery) const;

	/**
	 * Returns whether the collection contains the card.
	 * 
	 * @param Suit - The suit of the card to check for.
	 * @param Rank - The rank of the card to check for.
	 * @return `true` if and only if the collection contains the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool ContainsCardBySuitAndRank(ECardSuit Suit, ECardRank Rank) const;

	/**
	 * Returns the card specified by the suit and rank.
	 * 
	 * Returns `nullptr` if there is no card that matches the specified
	 * suit and rank.
	 *
	 * @param Suit - The suit of the card to get.
	 * @param Rank - The rank of the card to get.
	 * @return The card specified by the suit and rank or `nullptr`.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	ACard* GetCardBySuitAndRank(ECardSuit Suit, ECardRank Rank);

	/**
	 * Returns whether a new card can be added.
	 * 
	 * A card can be added if all of the following are true:
	 * 1. The collection is not full.
	 * 2. `ToAdd` is not a `nullptr`.
	 * 3. `ToAdd` is not already in the collection.
	 *
	 * @param ToAdd - The new card to add.
	 * @return `true` if and only if a new card can be added.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool CanAddCard(ACard* ToAdd) const;

	/**
	 * Adds a new card.
	 * 
	 * The card will be attached to this collection. The card's
	 * collision will be disabled.
	 *
	 * A card can be added if all of the following are true:
	 * 1. The collection is not full.
	 * 2. `ToAdd` is not a `nullptr`.
	 * 3. `ToAdd` is not already in the collection.
	 *
	 * @param ToAdd - The new card to add.
	 * @see CanAddCard(ACard*)
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	void AddCard(ACard* ToAdd);
};
