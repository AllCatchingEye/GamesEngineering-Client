// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardTrick.h"

ACardTrick::ACardTrick() : ACardStack()
{
	this->Cards.Reserve(ACardTrick::CARD_COUNT_MAX);
}



int32 ACardTrick::GetCardMaximum_Implementation() const
{
	return ACardTrick::CARD_COUNT_MAX;
}

void ACardTrick::AddCard_Implementation(ACard* ToAdd)
{
	
	Super::AddCard_Implementation(ToAdd);
	this->RearrangeCards();
}

void ACardTrick::RearrangeCards()
{

	const int32 CardCount = this->Cards.Num();

	ACard* Card;
	FVector CardLocation;
	FRotator CardRotation;
	for (int32 i = 0; i < CardCount; i++)
	{
		Card = this->Cards[i];

		// Reset card position:
		//Card->SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		CardLocation = FVector(-80.0, 20.0f * i, 175.0f);
		CardRotation = FRotator(0.0f, 0.0f, 0.0f);
		// Correct the card position.
		// TODO: Reimport the static mesh, so that the rotation does not have to be changed manually.
		CardRotation.Yaw = 90;

		Card->SetActorRelativeLocation(CardLocation);
		Card->SetActorRelativeRotation(CardRotation);
	}
}
