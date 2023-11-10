// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

ECardSuit UCard::getSuit() const {
	return this->Suit;
}

ECardRank UCard::getRank() const {
	return this->Rank;
}
