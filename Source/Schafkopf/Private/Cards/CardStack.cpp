// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardStack.h"

ACardStack::ACardStack()
{
	PrimaryActorTick.bCanEverTick = true;

	this->Cards = TArray<ACard*>();
}

int32 ACardStack::GetCardCount_Implementation() const
{
	return this->Cards.Num();
}

bool ACardStack::IsEmpty_Implementation() const
{
	return this->Cards.IsEmpty();
}

bool ACardStack::IsFull_Implementation() const
{
	return this->GetCardCount_Implementation() == this->GetCardMaximum_Implementation();
}

bool ACardStack::ContainsCard_Implementation(ACard* ToQuery) const
{
	return ToQuery && this->Cards.Contains(ToQuery);
}

bool ACardStack::CanAddCard_Implementation(ACard* ToAdd) const
{
	return !this->IsFull_Implementation() && !this->ContainsCard_Implementation(ToAdd);
}

void ACardStack::AddCard_Implementation(ACard* ToAdd)
{
	verify(this->CanAddCard_Implementation(ToAdd));

	ToAdd->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	this->Cards.Add(ToAdd);
}

void ACardStack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACardStack::BeginPlay()
{
	Super::BeginPlay();
}