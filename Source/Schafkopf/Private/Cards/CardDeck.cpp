// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardDeck.h"

ACardDeck::ACardDeck() : ACardStackExtended()
{
	this->Cards.Reserve(ACardDeck::CARD_COUNT_MAX);
}

int32 ACardDeck::GetCardMaximum_Implementation() const
{
	return ACardDeck::CARD_COUNT_MAX;
}
