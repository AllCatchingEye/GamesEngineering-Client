// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameMoney.h"
#include <Core/SKCharacter.h>
#include <Core/SKPlayerController.h>
#include <Core/SKGameInstance.h>

void UGameMoney::UpdateMoneyUI(int32 money)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::White, FString::Printf(TEXT("Money of player: %d"), money));

	int32 euro = money / 100;
	int32 cents = money % 100;
	this->moneyUI = FString::Printf(TEXT("%d,%d \u20ac"), euro, cents); // \u20ac == Unicode for €
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::White, FString::Printf(TEXT("Euro, Cents: %d, %d"), euro, cents));
}
