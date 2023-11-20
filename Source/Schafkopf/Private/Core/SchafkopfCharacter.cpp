// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfCharacter.h"
#include "Kismet/KismetMathLibrary.h"

ASchafkopfCharacter::ASchafkopfCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	this->Player = nullptr;
	this->CardHand = nullptr;
}

USchafkopfPlayer* ASchafkopfCharacter::GetPlayer()
{
	return this->Player;
}

ACardHand* ASchafkopfCharacter::GetCardHand() const
{
	return this->CardHand;
}

void ASchafkopfCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	this->CardHand = GetWorld()->SpawnActor<ACardHand>(ACardHand::StaticClass());
	this->CardHand->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
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
