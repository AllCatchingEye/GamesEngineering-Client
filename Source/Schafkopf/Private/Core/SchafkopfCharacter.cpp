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
	this->CardSpline->SetRelativeLocation(FVector(0.0f, -50.0f, 0.0f));
	this->CardSpline->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	this->CardSpline->bDrawDebug = true;

	this->CardSpline->ClearSplinePoints();
	this->CardSpline->AddPoint(FSplinePoint(0.0f, FVector(0.0f, 0.0f, 0.0f)));
	this->CardSpline->AddPoint(FSplinePoint(0.5f, FVector(5.0f, 50.0f, 20.0f)));
	this->CardSpline->AddPoint(FSplinePoint(1.0f, FVector(10.0f, 100.0f, 0.0f)));
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
	this->HandCards.Add(ToAdd);
	this->RearrangeHandCards();
}

void ASchafkopfCharacter::RemoveHandCard(ACard* ToRemove)
{
	verify(ToRemove != nullptr);
	verify(this->HandCards.Contains(ToRemove));
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
	// The spline duration in seconds.
	const float SplineDuration = this->CardSpline->Duration;
	// The initial fraction the cards are spaced apart form each other.
	const float SplineFractionBase = UKismetMathLibrary::SafeDivide(SplineDuration, this->GetHandCardAmount());
	// Make the cards be closer to each other.
	const float SplineFractionFinal = SplineFractionBase * 0.5f;

	ACard* Card;
	FTransform Transform;
	for (int32 i = 0; i < this->GetHandCardAmount(); i++)
	{
		Card = HandCards[i];
		Transform = this->CardSpline->GetTransformAtTime(SplineFractionFinal * i, ESplineCoordinateSpace::Local, true);

		Card->SetActorRelativeLocation(Transform.GetLocation());
		Card->SetActorRelativeRotation(Transform.GetRotation());
	}
}
