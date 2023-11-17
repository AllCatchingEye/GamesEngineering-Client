// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfCharacter.h"
#include "Kismet/KismetMathLibrary.h"

ASchafkopfCharacter::ASchafkopfCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	this->Player = nullptr;
	this->HandCards = TArray<ACard*>();
	this->HandCards.Reserve(this->HAND_CARDS_MAX);

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

USchafkopfPlayer* ASchafkopfCharacter::GetPlayer()
{
	return this->Player;
}

bool ASchafkopfCharacter::CanAddHandCard()
{
	return this->HandCards.Num() < this->HAND_CARDS_MAX;
}

int32 ASchafkopfCharacter::GetHandCardAmount()
{
	return this->HandCards.Num();
}

void ASchafkopfCharacter::AddHandCard(ACard* ToAdd)
{
	verify(ToAdd != nullptr);
	verify(this->CanAddHandCard());

	ToAdd->SetActorEnableCollision(false);
	ToAdd->AttachToComponent(this->CardSpline, FAttachmentTransformRules::SnapToTargetIncludingScale);
	this->HandCards.Add(ToAdd);
	this->RearrangeHandCards();
}

void ASchafkopfCharacter::RemoveHandCard(ACard* ToRemove)
{
	verify(ToRemove != nullptr);
	verify(this->HandCards.Contains(ToRemove));

	ToRemove->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	this->HandCards.Add(ToRemove);
	this->RearrangeHandCards();
}

void ASchafkopfCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASchafkopfCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASchafkopfCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASchafkopfCharacter::RearrangeHandCards()
{
	/** The spline duration in seconds. */
	const float SplineDuration = this->CardSpline->Duration;
	/** The initial fraction the cards are spaced apart form each other. */
	const float SplineFraction = UKismetMathLibrary::SafeDivide(SplineDuration, this->GetHandCardAmount());
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
	for (int32 i = 0; i < this->GetHandCardAmount(); i++)
	{
		Card = HandCards[i];

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
