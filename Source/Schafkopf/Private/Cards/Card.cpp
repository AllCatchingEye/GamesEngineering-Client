// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	this->CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	this->CardMesh->SetupAttachment(this->RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CardAsset(
		TEXT("/Game/Schafkopf/Cards/SM_Card.SM_Card")
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

const TStaticArray<UTexture2D*, ACard::CARD_TEXTURES_AMOUNT> ACard::CARD_TEXTURES = []() -> TStaticArray<UTexture2D*, ACard::CARD_TEXTURES_AMOUNT>
{
	TStaticArray<UTexture2D*, ACard::CARD_TEXTURES_AMOUNT> Textures;

	// Fetch the base card texture.
	// This texture is used for unknown cards.
	ConstructorHelpers::FObjectFinder<UTexture2D> TextureUnknown(
		TEXT("Texture2D'/Game/Cards/T_CardBack.T_CardBack'")
	);

	if (TextureUnknown.Succeeded())
	{
		Textures[0] = TextureUnknown.Object;
	}

	// Fetch all actual card textures.
	// The texture location string has the following form:
	// "Texture2D'/Game/FOLDER/SUB_FOLDER/.../TEXTURE_NAME.TEXTURE_NAME'"
	const FString CardTextureLocationStart = TEXT("Texture2D'/Game/Cards/");
	const FString CardTextureLocationConcatenator = TEXT(".");
	const FString CardTextureLocationEnd = TEXT("'");
	const FString CardTextureNameBase = TEXT("T_CardFront_");
	const FString CardTextureNameSeparator = TEXT("_");
	FString CardTextureNameFull;
	FString CardTextureLocationFull;
	uint8 EnumValueSuit;
	uint8 EnumValueRank;
	for (ECardSuit CardSuit : TEnumRange<ECardSuit>())
	{
		EnumValueSuit = (uint8)CardSuit;

		for (ECardRank CardRank : TEnumRange<ECardRank>())
		{
			// Construct the card texture name.
			EnumValueRank = (uint8)CardRank;
			CardTextureNameFull = CardTextureNameBase;
			CardTextureNameFull += FString::FromInt(EnumValueSuit);
			CardTextureNameFull += CardTextureNameSeparator;
			CardTextureNameFull += FString::FromInt(EnumValueRank);

			// Construct the card texture location.
			CardTextureLocationFull = CardTextureLocationStart;
			CardTextureLocationFull += CardTextureNameFull;
			CardTextureLocationFull += CardTextureLocationConcatenator;
			CardTextureLocationFull += CardTextureNameFull;
			CardTextureLocationFull += CardTextureLocationEnd;

			// Fetch the card texture.
			ConstructorHelpers::FObjectFinder<UTexture2D> Texture(*CardTextureLocationFull);

			if (Texture.Succeeded())
			{
				Textures[EnumValueSuit * EnumValueRank] = Texture.Object;
			}
		}
	}

	return Textures;
}();
