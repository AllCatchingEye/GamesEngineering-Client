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
