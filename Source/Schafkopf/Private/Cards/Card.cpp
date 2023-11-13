// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"

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

	//Get the front material and create a dynamic material instance for it.
	this->CardMaterialFront = this->CardMesh->GetMaterial(0);
	this->CardMaterialFrontDynamic = UMaterialInstanceDynamic::Create(this->CardMaterialFront, this);
	this->CardMesh->SetMaterial(0, this->CardMaterialFrontDynamic);

	//TODO: Create a method that loads/binds the texture to the dynamic material.
}

void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
