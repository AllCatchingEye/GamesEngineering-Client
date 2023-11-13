// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Cards/Card.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	this->CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	this->CardMesh->SetupAttachment(this->RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CardAsset(
		TEXT("/Game/Schafkopf/Core/Cards/SM_Card.SM_Card")
	);

	if (CardAsset.Succeeded())
	{
		this->CardMesh->SetStaticMesh(CardAsset.Object);
		this->CardMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
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
