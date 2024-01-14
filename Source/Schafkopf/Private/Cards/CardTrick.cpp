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

void ACardTrick::DisappearCards(ACardTrick* CardTrick)
{
	for (int32 i = 0; i < CardTrick->Cards.Num(); i++)
	{
		CardTrick->Cards[i]->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
	}
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

		//CardLocation = FVector(-80.0, (25.0f * i) - 50.0f, 175.0f);
		int xPos = 65 + (10 * i);
		int yPos = 260 + (6 * i);
		CardLocation = FVector(-xPos, yPos, 103.843386);
		CardRotation = FRotator(0.0f, 150.0f, 0);

		// Correct the card position.
		// TODO: Reimport the static mesh, so that the rotation does not have to be changed manually.
		CardRotation.Yaw = 150.0f;

		Card->SetActorRelativeLocation(CardLocation);
		Card->SetActorRelativeRotation(CardRotation);
	}
}
