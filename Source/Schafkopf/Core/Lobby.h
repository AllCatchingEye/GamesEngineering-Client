// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Lobby.generated.h"

/**
 * The Lobby class.
 * 
 * The Lobby represents the game room that the player is part of. A player can only
 * be part of one Lobby at a time, thus there can only be one Lobby object.
 * 
 * A Lobby always consits of four players. Of which at least one is a real player.
 * The remaining three may either be other real players or AI players.
 * 
 * //TODO: Add singleton pattern logic.
 */
UCLASS()
class SCHAFKOPF_API ULobby : public UObject
{
	GENERATED_BODY()

private:
	/** The ID of the lobby. The ID is immutable. */
	FName Id;
	
public:
	/**
	 * Returns the ID of the lobby.
	 * 
	 * The ID of the Lobby is immutable.
	 * 
	 * @return The ID of the lobby.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetId();

	/**
	 * Creates a new Lobby.
	 * 
	 * @param Id - The ID of the lobby.
	 * @return A new Lobby object.
	 */
	UFUNCTION(BlueprintCallable)
	static ULobby* Make(const FName Id);
};
