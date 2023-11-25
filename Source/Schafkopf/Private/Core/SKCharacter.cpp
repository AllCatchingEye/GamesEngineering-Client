// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SKCharacter.h"

#include "Cards/CardHand.h"

ASKCharacter::ASKCharacter() : ACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	this->CardHand = nullptr;
}

ACardHand* ASKCharacter::GetCardHand() const
{
	return this->CardHand;
}

void ASKCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	this->CardHand = GetWorld()->SpawnActor<ACardHand>(ACardHand::StaticClass());
	this->CardHand->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ASKCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASKCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASKCharacter::SetMoney(int newMoney)
{
	this->money = newMoney;
}

int ASKCharacter::GetMoney()
{
	return this->money;
}