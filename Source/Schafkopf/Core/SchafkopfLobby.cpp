// Fill out your copyright notice in the Description page of Project Settings.


#include "SchafkopfLobby.h"

FName USchafkopfLobby::GetId() {
	return this->Id;
}

USchafkopfLobby* USchafkopfLobby::Make(const FName Id) {
	USchafkopfLobby* NewLobby = NewObject<USchafkopfLobby>(nullptr, USchafkopfLobby::StaticClass());
	NewLobby->Id = Id;

	return NewLobby;
}
