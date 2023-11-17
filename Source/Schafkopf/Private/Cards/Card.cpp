// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"

ACard::ACard()
{
	PrimaryActorTick.bCanEverTick = false;

	this->CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	this->CardMesh->SetupAttachment(this->RootComponent);
	this->CardMesh->SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CardAsset(
		TEXT("StaticMesh'/Game/Schafkopf/Cards/SM_Card.SM_Card'")
	);

	if (CardAsset.Succeeded())
	{
		this->CardMesh->SetStaticMesh(CardAsset.Object);
		this->CardMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

ECardSuit ACard::GetSuit() const
{
	return this->Suit;
}

ECardRank ACard::GetRank() const
{
	return this->Rank;
}

void ACard::Update(const ECardSuit NewSuit, const ECardRank NewRank)
{
	const bool bIsNone = NewSuit == ECardSuit::NONE && NewRank == ECardRank::NONE;
	const bool bIsValid = NewSuit != ECardSuit::NONE && NewRank != ECardRank::NONE;
	if (ensureAlwaysMsgf(bIsNone || bIsValid, TEXT("Parameters `NewSuit` and `NewRank` must either both be NONE or none NONE."))	)
	{
		this->Suit = NewSuit;
		this->Rank = NewRank;
		this->UpdateFrontTexture();
	}
}

void ACard::BeginPlay()
{
	Super::BeginPlay();

	// Get the front material and create a dynamic material instance for it.
	this->CardMaterialFront = this->CardMesh->GetMaterial(0);
	this->CardMaterialFrontDynamic = UMaterialInstanceDynamic::Create(this->CardMaterialFront, this);
	this->CardMesh->SetMaterial(0, this->CardMaterialFrontDynamic);

	this->UpdateFrontTexture();
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
	Textures[0] = LoadObject<UTexture2D>(ACard::StaticClass(), TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardBack.T_CardBack'"));

	// Fetch all actual card textures.
	// The texture location string has the following form:
	// "Texture2D'/Game/GAME_NAME/FOLDER/SUB_FOLDER/.../TEXTURE_NAME.TEXTURE_NAME'"
	const FString CardTextureLocationStart = TEXT("Texture2D'/Game/Schafkopf/Cards/");
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
			CardTextureNameFull += FString::FromInt(EnumValueSuit - 1);
			CardTextureNameFull += CardTextureNameSeparator;
			CardTextureNameFull += FString::FromInt(EnumValueRank - 1);

			// Construct the card texture location.
			CardTextureLocationFull = CardTextureLocationStart;
			CardTextureLocationFull += CardTextureNameFull;
			CardTextureLocationFull += CardTextureLocationConcatenator;
			CardTextureLocationFull += CardTextureNameFull;
			CardTextureLocationFull += CardTextureLocationEnd;

			// Fetch the card texture.
			Textures[EnumValueSuit * EnumValueRank] = LoadObject<UTexture2D>(ACard::StaticClass(), *CardTextureLocationFull);
		}
	}

	return Textures;
}();


void ACard::UpdateFrontTexture()
{
	// Bind the card texture based on the rank and suit enum.
	const uint8 EnumValueSuit = (uint8)this->Suit;
	const uint8 EnumValueRank = (uint8)this->Rank;
	UTexture2D* CardTexture = ACard::CARD_TEXTURES[EnumValueSuit * EnumValueRank];

	ensureMsgf(CardTexture != nullptr, TEXT("Card texture [ %d, %d ] was null."), EnumValueSuit, EnumValueRank);
	this->CardMaterialFrontDynamic->SetTextureParameterValue(TEXT("Texture"), CardTexture);
}
