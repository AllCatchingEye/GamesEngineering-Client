// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/Card.h"

ACard::ACard()
{
	this->PrimaryActorTick.bCanEverTick = false;

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
		this->CardMesh->SetRenderCustomDepth(true);
	}

	{
		// Absolutely dirty fix part 2:
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTextureBack(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardBack.T_CardBack'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture01(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_0.T_CardFront_0_0'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture02(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_1.T_CardFront_0_1'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture03(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_2.T_CardFront_0_2'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture04(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_3.T_CardFront_0_3'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture05(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_4.T_CardFront_0_4'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture06(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_5.T_CardFront_0_5'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture07(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_6.T_CardFront_0_6'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture08(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_0_7.T_CardFront_0_7'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture09(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_0.T_CardFront_1_0'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture10(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_1.T_CardFront_1_1'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture11(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_2.T_CardFront_1_2'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture12(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_3.T_CardFront_1_3'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture13(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_4.T_CardFront_1_4'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture14(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_5.T_CardFront_1_5'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture15(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_6.T_CardFront_1_6'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture16(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_1_7.T_CardFront_1_7'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture17(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_0.T_CardFront_2_0'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture18(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_1.T_CardFront_2_1'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture19(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_2.T_CardFront_2_2'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture20(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_3.T_CardFront_2_3'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture21(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_4.T_CardFront_2_4'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture22(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_5.T_CardFront_2_5'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture23(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_6.T_CardFront_2_6'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture24(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_2_7.T_CardFront_2_7'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture25(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_0.T_CardFront_3_0'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture26(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_1.T_CardFront_3_1'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture27(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_2.T_CardFront_3_2'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture28(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_3.T_CardFront_3_3'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture29(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_4.T_CardFront_3_4'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture30(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_5.T_CardFront_3_5'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture31(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_6.T_CardFront_3_6'"));
		static ConstructorHelpers::FObjectFinder<UTexture2D> CardTexture32(TEXT("Texture2D'/Game/Schafkopf/Cards/T_CardFront_3_7.T_CardFront_3_7'"));

		ACard::CARD_TEXTURES[ 0] = CardTextureBack.Object;
		ACard::CARD_TEXTURES[ 1] = CardTexture01.Object;
		ACard::CARD_TEXTURES[ 2] = CardTexture02.Object;
		ACard::CARD_TEXTURES[ 3] = CardTexture03.Object;
		ACard::CARD_TEXTURES[ 4] = CardTexture04.Object;
		ACard::CARD_TEXTURES[ 5] = CardTexture05.Object;
		ACard::CARD_TEXTURES[ 6] = CardTexture06.Object;
		ACard::CARD_TEXTURES[ 7] = CardTexture07.Object;
		ACard::CARD_TEXTURES[ 8] = CardTexture08.Object;
		ACard::CARD_TEXTURES[ 9] = CardTexture09.Object;
		ACard::CARD_TEXTURES[10] = CardTexture10.Object;
		ACard::CARD_TEXTURES[11] = CardTexture11.Object;
		ACard::CARD_TEXTURES[12] = CardTexture12.Object;
		ACard::CARD_TEXTURES[13] = CardTexture13.Object;
		ACard::CARD_TEXTURES[14] = CardTexture14.Object;
		ACard::CARD_TEXTURES[15] = CardTexture15.Object;
		ACard::CARD_TEXTURES[16] = CardTexture16.Object;
		ACard::CARD_TEXTURES[17] = CardTexture17.Object;
		ACard::CARD_TEXTURES[18] = CardTexture18.Object;
		ACard::CARD_TEXTURES[19] = CardTexture19.Object;
		ACard::CARD_TEXTURES[20] = CardTexture20.Object;
		ACard::CARD_TEXTURES[21] = CardTexture21.Object;
		ACard::CARD_TEXTURES[22] = CardTexture22.Object;
		ACard::CARD_TEXTURES[23] = CardTexture23.Object;
		ACard::CARD_TEXTURES[24] = CardTexture24.Object;
		ACard::CARD_TEXTURES[25] = CardTexture25.Object;
		ACard::CARD_TEXTURES[26] = CardTexture26.Object;
		ACard::CARD_TEXTURES[27] = CardTexture27.Object;
		ACard::CARD_TEXTURES[28] = CardTexture28.Object;
		ACard::CARD_TEXTURES[29] = CardTexture29.Object;
		ACard::CARD_TEXTURES[30] = CardTexture30.Object;
		ACard::CARD_TEXTURES[31] = CardTexture31.Object;
		ACard::CARD_TEXTURES[32] = CardTexture32.Object;

		static ConstructorHelpers::FObjectFinder<UMaterialInterface> CardGreyedOut(TEXT("Material'/Game/Schafkopf/Cards/M_CardGreyedOut.M_CardGreyedOut'"));
		ACard::CardMaterialGreyedOut = CardGreyedOut.Object;
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

bool ACard::IsGreyedOut() const
{
	return this->CardMesh->GetOverlayMaterial() != nullptr;
}

void ACard::SetGreyedOut(bool bShouldBeGreyedOut)
{
	if (bShouldBeGreyedOut)
	{
		this->CardMesh->SetOverlayMaterial(ACard::CardMaterialGreyedOut);
	}
	else
	{
		this->CardMesh->SetOverlayMaterial(nullptr);
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

	this->CardMesh->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
}

void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Absolutely dirty fix part 1:
TStaticArray<UTexture2D*, ACard::CARD_TEXTURES_AMOUNT> ACard::CARD_TEXTURES = TStaticArray<UTexture2D*, ACard::CARD_TEXTURES_AMOUNT>();
UMaterialInterface* ACard::CardMaterialGreyedOut = nullptr;

void ACard::UpdateFrontTexture()
{

	int32 CardTextureIndex = 0;

	const uint8 EnumValueSuit = (uint8)this->Suit;
	const uint8 EnumValueRank = (uint8)this->Rank;

	const bool bIsNone = this->Suit == ECardSuit::NONE && this->Rank == ECardRank::NONE;
	const bool bIsValid = this->Suit != ECardSuit::NONE && this->Rank != ECardRank::NONE;
	ensureAlwaysMsgf(
		(bIsNone || bIsValid),
		TEXT("Parameters `NewSuit` and `NewRank` must either both be NONE or none NONE.")
	);

	if (bIsValid)
	{
		// Bind the card texture based on the rank and suit enum.
		CardTextureIndex = ((EnumValueSuit - 1) * 8) + EnumValueRank;
	}

	UTexture2D* CardTexture = ACard::CARD_TEXTURES[CardTextureIndex];
	//checkf(CardTexture != nullptr, TEXT("Card texture [ %d ] was null."), EnumValueSuit, EnumValueRank)

	this->CardMaterialFrontDynamic->SetTextureParameterValue(TEXT("Texture"), CardTexture);
}
