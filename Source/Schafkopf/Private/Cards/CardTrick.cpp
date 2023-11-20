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
