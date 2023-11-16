// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfCharacter.h"

ASchafkopfCharacter::ASchafkopfCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	this->Player = nullptr;
	this->HandCards = TArray<ACard*>();
	this->HandCards.Reserve(this->HAND_CARDS_MAX);

	this->CardSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Card Spline"));
	this->CardSpline->SetupAttachment(this->RootComponent);
	this->CardSpline->SetRelativeLocation(FVector(0.0f, -50.0f, 0.0f));
	this->CardSpline->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	this->CardSpline->bDrawDebug = true;

	this->CardSpline->ClearSplinePoints();
	this->CardSpline->AddPoint(FSplinePoint(0.0f, FVector(0.0f, 0.0f, 0.0f)));
	this->CardSpline->AddPoint(FSplinePoint(0.5f, FVector(50.0f, 0.0f, 20.0f)));
	this->CardSpline->AddPoint(FSplinePoint(1.0f, FVector(100.0f, 0.0f, 0.0f)));
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
}

void ASchafkopfCharacter::RemoveHandCard(ACard* ToRemove)
{
	verify(ToRemove != nullptr);
	verify(this->HandCards.Contains(ToRemove));
	this->HandCards.Add(ToRemove);
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
