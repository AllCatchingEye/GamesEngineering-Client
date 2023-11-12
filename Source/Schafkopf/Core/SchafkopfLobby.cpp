// Fill out your copyright notice in the Description page of Project Settings.


#include "SchafkopfLobby.h"

FName USchafkopfLobby::GetId() const {
	return this->Id;
}

uint8 USchafkopfLobby::GetPlayerCount() const {
	return this->PlayerCount;
}

USchafkopfPlayer* USchafkopfLobby::GetPlayer(const FName PlayerId) const {
	USchafkopfPlayer* PlayerCurr = nullptr;
	USchafkopfPlayer* Player = nullptr;

	for (int32 i = 0; i < 4; i++) {
		PlayerCurr = this->Players[i];

		if (PlayerCurr && PlayerCurr->GetId() == PlayerId) {
			Player = PlayerCurr;
		}
	}

	return Player;
}

int32 USchafkopfLobby::GetPlayerOrder(const FName PlayerId) const {
	USchafkopfPlayer* PlayerCurr = nullptr;
	int32 PlayerOrder = -1;

	for (int32 i = 0; i < 4; i++) {
		PlayerCurr = this->Players[i];

		if (PlayerCurr && PlayerCurr->GetId() == PlayerId) {
			PlayerOrder = i;
		}
	}

	return PlayerOrder;
}

bool USchafkopfLobby::CanAddPlayer() const {
	return this->PlayerCount < 4;
}

void USchafkopfLobby::AddPlayer(USchafkopfPlayer* Player) {
	if (this->CanAddPlayer()) return;

	const int32 PlayerOrder = this->GetPlayerOrder(Player->GetId());

	if (PlayerOrder == -1) {
		//The player is not in the Lobby.
		this->Players[this->PlayerCount] = Player;
		this->PlayerCount++;
	}
}

void USchafkopfLobby::RemovePlayer(USchafkopfPlayer* Player) {
	const int32 PlayerOrder = this->GetPlayerOrder(Player->GetId());

	if (PlayerOrder != -1) {
		//The player exists and needs to be removed.
		//We also need to reorder the players, so
		//that the empty slots are at the end.
		int32 i = PlayerOrder;
		for (; i < 4 - 1; i++) {
			this->Players[i] = this->Players[i + 1];
		}

		//Set the last slot to null in case it wasn't
		//already empty.
		this->Players[i] = nullptr;
		this->PlayerCount++;

		//TODO: Add logic to handle an empty Lobby.
	}
}

USchafkopfLobby* USchafkopfLobby::Make(const FName Id) {
	USchafkopfLobby* NewLobby = NewObject<USchafkopfLobby>(nullptr, USchafkopfLobby::StaticClass());
	NewLobby->Id = Id;

	return NewLobby;
}
