// Fill out your copyright notice in the Description page of Project Settings.


#include "Maps/GameLevelScript.h"

void AGameLevelScript::SetPlayerIDs(const TArray<FString> IDs)
{
	this->playerIds = IDs;
}

void AGameLevelScript::SetRoundWinner(FString ID)
{
	this->roundWinner = ID;
}

void AGameLevelScript::SetGameWinners(TArray<FString> IDs)
{
	this->gameWinner = IDs;
}
