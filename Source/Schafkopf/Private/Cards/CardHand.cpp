// Fill out your copyright notice in the Description page of Project Settings.


#include "Cards/CardHand.h"
#include "Core/WSMessage.h"

#include "Kismet/KismetMathLibrary.h"

ACardHand::ACardHand() : ACardStackExtended()
{
	this->Cards = TArray<ACard*>();
	this->Cards.Reserve(ACardHand::CARD_COUNT_MAX);

	this->CardSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Card Spline"));
	this->CardSpline->SetupAttachment(this->RootComponent);
	this->CardSpline->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	this->CardSpline->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	this->CardSpline->bDrawDebug = true;

	this->CardSpline->ClearSplinePoints();
	this->CardSpline->AddPoint(FSplinePoint(0.0f, FVector(0.0f, -50.0f, 0.0f), ESplinePointType::CurveClamped));
	this->CardSpline->AddPoint(FSplinePoint(1.0f, FVector(5.0f, 0.0f, 20.0f), ESplinePointType::CurveClamped));
	this->CardSpline->AddPoint(FSplinePoint(2.0f, FVector(10.0f, 50.0f, 0.0f), ESplinePointType::CurveClamped));
	this->CardSpline->UpdateSpline();
}

int32 ACardHand::GetCardMaximum_Implementation() const
{
	return ACardHand::CARD_COUNT_MAX;
}

void ACardHand::AddCard_Implementation(ACard* ToAdd)
{
	Super::AddCard_Implementation(ToAdd);
	this->RearrangeCards();
}

void ACardHand::RemoveCard_Implementation(ACard* ToRemove)
{
	Super::RemoveCard_Implementation(ToRemove);
	this->RearrangeCards();
}

void ACardHand::GreyOutCards(TArray<FWSCard>& PlayableCards)
{
	bool bIsPlayable = false;
	ACard* CurrentCard = nullptr;
	ECardSuit CurrentCardSuit = ECardSuit::NONE;
	ECardRank CurrentCardRank = ECardRank::NONE;
	for (int32 i = 0; i < this->GetCardCount_Implementation(); i++)
	{
		bIsPlayable = false;
		CurrentCard = this->Cards[i];
		for (int32 j = 0; j < PlayableCards.Num(); j++)
		{
			CurrentCardSuit = GetCardSuitFromString(PlayableCards[j].suit);
			CurrentCardRank = GetCardRankFromString(PlayableCards[j].rank);

			bIsPlayable = bIsPlayable || (
				CurrentCard->GetSuit() == CurrentCardSuit &&
				CurrentCard->GetRank() == CurrentCardRank
			);
		}

		if (!bIsPlayable)
		{
			CurrentCard->SetGreyedOut(true);
		}
	}
}

void ACardHand::ResetGreyedOutCards()
{
	// Reset the grey out overlay of all cards.
	for (int32 i = 0; i < this->GetCardCount_Implementation(); i++)
	{
		this->Cards[i]->SetGreyedOut(false);
	}
}

void ACardHand::RearrangeCards()
{
	const int32 CardCount = this->Cards.Num();
	/** The spline duration in seconds. */
	const float SplineDuration = this->CardSpline->Duration;
	/** The initial fraction the cards are spaced apart form each other. */
	const float SplineFraction = UKismetMathLibrary::SafeDivide(SplineDuration, CardCount);
	/** The offset to the initial fraction. */
	const float SplineFractionOffset = SplineFraction * 0.5f;
	/**
	 * The spline length adjustment factor.
	 * A factor of less than 1 causes the cards to overlap more.
	 */
	const float SplineLengthFactor = 0.5f;
	/**
	 * The offset to the center of the spline.
	 * The get the offset, the duration needs to be adjusted by the length factor.
	 */
	const float SplineOffset = SplineDuration * SplineLengthFactor;

	ACard* Card;
	float SplineTime;
	FVector CardLocation;
	FRotator CardRotation;
	for (int32 i = 0; i < CardCount; i++)
	{
		Card = this->Cards[i];

		// Reset card position:
		//Card->SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		// Compute the base position.
		SplineTime = SplineFractionOffset + SplineFraction * i;
		// Offset the cards to the center.
		SplineTime += SplineOffset;
		// Scale the total length.
		SplineTime *= SplineLengthFactor;

		CardLocation = this->CardSpline->GetLocationAtTime(SplineTime, ESplineCoordinateSpace::Local, false);
		CardRotation = this->CardSpline->GetRotationAtTime(SplineTime, ESplineCoordinateSpace::Local, false);
		// Correct the card position.
		// TODO: Reimport the static mesh, so that the rotation does not have to be changed manually.
		CardRotation.Yaw = 90;

		Card->SetActorRelativeLocation(CardLocation);
		Card->SetActorRelativeRotation(CardRotation);
	}
}
