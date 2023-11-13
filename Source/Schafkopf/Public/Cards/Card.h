// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardSuit.h"
#include "CardRank.h"
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
	ECardSuit Suit = ECardSuit::NONE;
	/** The rank of the card. */
	ECardRank Rank = ECardRank::NONE;

	/** The static mesh of the card. */
	UStaticMeshComponent* CardMesh = nullptr;
	/** The front material of the card's static mesh. */
	UMaterialInterface* CardMaterialFront = nullptr;
	/** The dynamic material instance of the card's front material. */
	UMaterialInstanceDynamic* CardMaterialFrontDynamic = nullptr;
};
