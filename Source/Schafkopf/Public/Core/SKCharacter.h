// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "SKCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SCHAFKOPF_API ASKCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASKCharacter();

	/**
	 * Returns the card hand of the player.
	 * 
	 * @return The card hand of the player.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class ACardHand* GetCardHand() const;

	/**
	 * Adds a new card to the list of playable cards.
	 * 
	 * If the specified card is a null pointer nothing happens.
	 * 
	 * @param PlayableCard - The new playable card.
	 */
	void AddPlayableCard(class ACard* PlayableCard);

	/**
	 * Returns whether the specified card is a playable card.
	 * 
	 * @param Card - The card to check.
	 * @returns `true` if and only if the specified card is a playable card.
	 */
	bool IsPlayableCard(class ACard* Card);

	/**
	 * Returns the index of the specified card.
	 *
	 * @param Card - The card to check.
	 * @returns The index of the specified card.
	 */
	int32 GetPlayableCardIndex(class ACard* Card);

	/** Clears the list of playable cards. */
	void ResetPlayableCards();

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetMoney(int32 newMoney);

	int32 GetMoney();

protected:
	virtual void BeginPlay() override;

private:
	/** The hand cards of the player. */
	class ACardHand* CardHand;

	/** The cards that the player may select. */
	TArray<class ACard*> PlayableCards;

	int32 money;
};
