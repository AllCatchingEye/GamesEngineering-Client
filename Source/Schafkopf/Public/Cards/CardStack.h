// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Cards/CardCollection.h"
#include "CardStack.generated.h"

/**
 * The abstract CardStack class.
 * 
 * A CardStack is a collection of cards. This basic implementation only allows
 * the adding of cards. The number of cards a CardStack can hold is determined
 * by the specific child class.
 */
UCLASS(Abstract, BlueprintType)
class SCHAFKOPF_API ACardStack : public AActor, public ICardCollection
{
	GENERATED_BODY()
	
public:	
	ACardStack();

	virtual int32 GetCardMaximum_Implementation() const PURE_VIRTUAL(ACardStack::GetCardMaximum, return -1;);

	UFUNCTION(BlueprintCallable, Category = "Cards")
	virtual int32 GetCardCount_Implementation() const final;

	virtual bool IsEmpty_Implementation() const final;

	virtual bool IsFull_Implementation() const final;

	virtual bool ContainsCard_Implementation(ACard* ToQuery) const final;

	virtual bool ContainsCardBySuitAndRank_Implementation(ECardSuit Suit, ECardRank Rank) const final;

	virtual ACard* GetCardBySuitAndRank_Implementation(ECardSuit Suit, ECardRank Rank) const final;

	virtual bool CanAddCard_Implementation(ACard* ToAdd) const final;

	virtual void AddCard_Implementation(ACard* ToAdd) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/** The array of cards of this CardCollection. */
	TArray<ACard*> Cards;
};
