// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfPlayer.h"

FName USchafkopfPlayer::GetId() {
	return this->Id;
}

USchafkopfPlayer* USchafkopfPlayer::Make(const FName Id) {
	USchafkopfPlayer* NewPlayer = NewObject<USchafkopfPlayer>(nullptr, USchafkopfPlayer::StaticClass());
	NewPlayer->Id = Id;

	return NewPlayer;
}
