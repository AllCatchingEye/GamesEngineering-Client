// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SKCharacter.h"

#include "Cards/Card.h"
#include "Cards/CardHand.h"

ASKCharacter::ASKCharacter() : ACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	this->CardHand = nullptr;
	this->PlayableCards = TArray<ACard*>();
}

ACardHand* ASKCharacter::GetCardHand() const
{
	return this->CardHand;
}

void ASKCharacter::AddPlayableCard(ACard* PlayableCard)
{
	if (PlayableCard)
	{
		this->PlayableCards.Add(PlayableCard);
	}
}

bool ASKCharacter::IsPlayableCard(ACard* Card)
{
	return this->PlayableCards.Contains(Card);
}

int32 ASKCharacter::GetPlayableCardIndex(ACard* Card)
{
	return this->PlayableCards.Find(Card);
}

void ASKCharacter::ResetPlayableCards()
{
	this->PlayableCards.Empty();
}

void ASKCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	this->CardHand = GetWorld()->SpawnActor<ACardHand>(ACardHand::StaticClass());
	this->CardHand->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ASKCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASKCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASKCharacter::SetMoney(int32 newMoney)
{
	this->money = newMoney;
}

int32 ASKCharacter::GetMoney()
{
	return this->money;
}
