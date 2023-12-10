// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

void UGameHUD::UpdateMoney(int32 NewMoney)
{
	const int32 Euro = NewMoney / 100;
	const int32 Cents = std::abs(NewMoney % 100);

	// The Unicode value for `€` is `\u20ac`.
	const FString FormattedString = FString::Printf(TEXT("%d,%d \u20ac"), Euro, Cents);
	this->Money = FText::FromString(FormattedString);
}

void UGameHUD::UpdateGameType(FText NewGameType)
{
	this->GameType = NewGameType;
}
