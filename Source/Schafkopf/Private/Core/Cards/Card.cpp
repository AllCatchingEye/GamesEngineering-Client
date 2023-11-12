// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Cards/Card.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;
}

ECardSuit ACard::getSuit() const
{
	return this->Suit;
}

ECardRank ACard::getRank() const
{
	return this->Rank;
}

void ACard::BeginPlay()
{
	Super::BeginPlay();

}

void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
