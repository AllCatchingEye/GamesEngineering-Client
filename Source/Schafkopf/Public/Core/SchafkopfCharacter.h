// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineComponent.h"

#include "Core/SchafkopfPlayer.h"
#include "Cards/Card.h"

#include "SchafkopfCharacter.generated.h"

UCLASS()
class SCHAFKOPF_API ASchafkopfCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASchafkopfCharacter();

	/**
	 * Returns the backing player.
	 * 
	 * @return The backing player.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USchafkopfPlayer* GetPlayer();

	/**
	 * Returns whether a new card can be added to the player's hand.
	 *
	 * @return `true` if and only if a new card can be added.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanAddHandCard();

	/**
	 * Returns the amount of hand cards.
	 *
	 * @return The amount of hand cards.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetHandCardAmount();

	/**
	 * Adds a new card to the player's hand.
	 * 
	 * Does not accept `nullptr`.
	 * 
	 * @param ToAdd - The new card to add.
	 */
	UFUNCTION(BlueprintCallable)
	void AddHandCard(ACard* ToAdd);

	/**
	 * Removes a card from the player's hand.
	 * 
	 * Does not accept `nullptr`.
	 *
	 * @param ToRemove - The new card to remove.
	 */
	UFUNCTION(BlueprintCallable)
	void RemoveHandCard(ACard* ToRemove);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** The maximum amount of hand cards. */
	static const int32 HAND_CARDS_MAX = 8;

	/** The backing player. */
	USchafkopfPlayer* Player;
	/** The list of hand cards. */
	TArray<ACard*> HandCards;

	/** The spline along which the cards will be arranged. */
	USplineComponent* CardSpline;
};
