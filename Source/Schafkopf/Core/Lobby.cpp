// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby.h"

FName ULobby::GetId() {
	return this->Id;
}

ULobby* ULobby::Make(const FName Id) {
	ULobby* NewLobby = NewObject<ULobby>(nullptr, ULobby::StaticClass());
	NewLobby->Id = Id;

	return NewLobby;
}
