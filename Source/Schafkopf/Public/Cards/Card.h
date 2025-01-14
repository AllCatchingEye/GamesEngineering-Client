// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Cards/CardSuit.h"
#include "Cards/CardRank.h"
#include "Card.generated.h"

/**
 * The Card class.
 */
UCLASS(BlueprintType)
class SCHAFKOPF_API ACard : public AActor
{
	GENERATED_BODY()

public:
	ACard();

	/**
	 * Returns the suit of the card.
	 *
	 * @return The suit of the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECardSuit GetSuit() const;

	/**
	 * Returns the rank of the card.
	 *
	 * @return The rank of the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECardRank GetRank() const;

	/**
	 * Updates the card.
	 * 
	 * Ensures that both `NewSuit` and `NewRank` are either `NONE` or none `NONE`.
	 * 
	 * @param NewSuit - The new suit of the card.
	 * @param NewRank - The new rank of the card.
	 */
	UFUNCTION(BlueprintCallable)
	void Update(const ECardSuit NewSuit, const ECardRank NewRank);

	/**
	 * Returns whether this actor is greyed out.
	 *
	 * @return `true` if and only if the actor is greyed out.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsGreyedOut() const;

	/**
	 * Sets whether this actor is greyed out.
	 *
	 * @param bShouldBeGreyedOut - `true` if and only if the actor should be greyed out.
	 */
	UFUNCTION(BlueprintCallable)
	void SetGreyedOut(bool bShouldBeGreyedOut);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** The suit of the card. */
	ECardSuit Suit = ECardSuit::NONE;
	/** The rank of the card. */
	ECardRank Rank = ECardRank::NONE;

	/** The static mesh of the card. */
	UStaticMeshComponent* CardMesh = nullptr;
	/** The front material of the card's static mesh. */
	UMaterialInterface* CardMaterialFront = nullptr;
	/** The dynamic material instance of the card's front material. */
	UMaterialInstanceDynamic* CardMaterialFrontDynamic = nullptr;

	/** The amount of statically loaded card textures. */
	static const int32 CARD_TEXTURES_AMOUNT = 33;
	/**
	 * A list of all statically loaded card textures.
	 * 
	 * This array contains 33 textures. The first one is the texture that will be
	 * used for cards that are not known to the client. This applies to for example:
	 * 1. The initial card stack. A stack of cards that has yet to be distributed
	 *    the players. Serves a client-only role for animation purposes.
	 * 2. The hand cards of oppenents, which's card value is not visible to this
	 *    client.
	 * 
	 * The other 32 cards (from index 1 to 33) are the actual card textures.
	 */
	static TStaticArray<UTexture2D*, CARD_TEXTURES_AMOUNT> CARD_TEXTURES;
	/** The material that is used to grey out a card. */
	static UMaterialInterface* CardMaterialGreyedOut;

	/** Updates the front texture of the card. */
	void UpdateFrontTexture();
};
