// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfLobby.h"

FName USchafkopfLobby::GetId() const
{
	return this->Id;
}

int32 USchafkopfLobby::GetPlayerCount() const
{
	return this->PlayerCount;
}

USchafkopfPlayer* USchafkopfLobby::GetPlayer(const FName PlayerId) const
{
	USchafkopfPlayer* PlayerCurr = nullptr;
	USchafkopfPlayer* Player = nullptr;

	for (int32 i = 0; i < USchafkopfLobby::PLAYER_COUNT_MAX; i++)
	{
		PlayerCurr = this->Players[i];

		if (PlayerCurr && PlayerCurr->GetId() == PlayerId)
		{
			Player = PlayerCurr;
		}
	}

	return Player;
}

int32 USchafkopfLobby::GetPlayerOrder(const FName PlayerId) const
{
	USchafkopfPlayer* PlayerCurr = nullptr;
	int32 PlayerOrder = USchafkopfLobby::PLAYER_NOT_PRESENT;

	for (int32 i = 0; i < USchafkopfLobby::PLAYER_COUNT_MAX; i++)
	{
		PlayerCurr = this->Players[i];

		if (PlayerCurr && PlayerCurr->GetId() == PlayerId)
		{
			PlayerOrder = i;
		}
	}

	return PlayerOrder;
}

bool USchafkopfLobby::CanAddPlayer() const
{
	return this->PlayerCount < USchafkopfLobby::PLAYER_COUNT_MAX;
}

void USchafkopfLobby::AddPlayer(USchafkopfPlayer* Player)
{
	if (this->CanAddPlayer()) return;

	const int32 PlayerOrder = this->GetPlayerOrder(Player->GetId());

	if (PlayerOrder == USchafkopfLobby::PLAYER_NOT_PRESENT)
	{
		//The player is not in the Lobby.
		this->Players[this->PlayerCount] = Player;
		this->PlayerCount++;
	}
}

void USchafkopfLobby::RemovePlayer(USchafkopfPlayer* Player)
{
	const int32 PlayerOrder = this->GetPlayerOrder(Player->GetId());

	if (PlayerOrder != USchafkopfLobby::PLAYER_NOT_PRESENT)
	{
		//The player exists and needs to be removed.
		//We also need to reorder the players, so
		//that the empty slots are at the end.
		int32 i = PlayerOrder;
		for (; i < USchafkopfLobby::PLAYER_COUNT_MAX - 1; i++)
		{
			this->Players[i] = this->Players[i + 1];
		}

		//Set the last slot to null in case it wasn't
		//already empty.
		this->Players[i] = nullptr;
		this->PlayerCount++;

		//TODO: Add logic to handle an empty Lobby.
	}
}

int32 USchafkopfLobby::GetPlayerCountMax()
{
	return USchafkopfLobby::PLAYER_COUNT_MAX;
}

USchafkopfLobby* USchafkopfLobby::Make(const FName Id)
{
	USchafkopfLobby* NewLobby = NewObject<USchafkopfLobby>(nullptr, USchafkopfLobby::StaticClass());
	NewLobby->Id = Id;

	return NewLobby;
}
