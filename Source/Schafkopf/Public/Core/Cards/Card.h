// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

/**
 * The CardSuit enum.
 * 
 * Provides a list of all available suits, that a card may have.
 * 
 * The value of `NONE` is used exclusively in cases where a client
 * should not be aware of the actual card. For example: Any cards
 * that are in the hand of another player should not be known to
 * the current player. The server obviously always knows about all
 * cards, and thus does not need the `NONE` value.
 */
UENUM(BlueprintType)
enum class ECardSuit : uint8
{
	NONE = 0		UMETA(DisplayName = "NONE"),
	EICHEL = 1		UMETA(DispalyName = "EICHEL"),
	GRAS = 2		UMETA(DispalyName = "GRAS"),
	HERZ = 3		UMETA(DispalyName = "HERZ"),
	SCHELLEN = 4	UMETA(DispalyName = "SCHELLEN")
};

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
	ECardSuit getSuit() const;
	/**
	 * Returns the rank of the card.
	 *
	 * @return The rank of the card.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ECardRank getRank() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** The suit of the card. */
	ECardSuit Suit;
	/** The rank of the card. */
	ECardRank Rank;

	/** The static mesh of the card. */
	UStaticMeshComponent* CardMesh;
};
