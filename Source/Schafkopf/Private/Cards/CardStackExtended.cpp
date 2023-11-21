// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardStackExtended.h"

ACardStackExtended::ACardStackExtended() : ACardStack()
{

}

bool ACardStackExtended::CanRemoveCard_Implementation(ACard* ToRemove) const
{
	return this->ContainsCard_Implementation(ToRemove);
}

void ACardStackExtended::RemoveCard_Implementation(ACard* ToRemove)
{
	verify(this->CanRemoveCard_Implementation(ToRemove));

	ToRemove->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	this->Cards.Remove(ToRemove);
}

void ACardStackExtended::RemoveCardByRankAndSuit_Implementation(ECardRank Rank, ECardSuit Suit)
{
	ACard* card = nullptr;

	for (int32 i = 0; i < this->Cards.Num(); i++)
	{
		if (this->Cards[i]->GetRank() == Rank && this->Cards[i]->GetSuit() == Suit)
		{
			card = this->Cards[i];
			this->RemoveCard_Implementation(this->Cards[i]);
			break;
		}
	}

	card->Destroy();
}