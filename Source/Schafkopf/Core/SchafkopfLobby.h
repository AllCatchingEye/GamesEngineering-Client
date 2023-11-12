// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SchafkopfPlayer.h"
#include "SchafkopfLobby.generated.h"

/**
 * The SchafkopfLobby class.
 * 
 * The Lobby represents the game room that the player is part of. A player can only
 * be part of one Lobby at a time, thus there can only be one Lobby object.
 * 
 * A Lobby always consits of four players. Of which at least one is a real player.
 * The remaining three may either be other real players or AI players.
 * 
 * Empty slots will be filled with AI players upon game start.
 * 
 * //TODO: Add singleton pattern logic.
 */
UCLASS()
class SCHAFKOPF_API USchafkopfLobby : public UObject
{
	GENERATED_BODY()

private:
	/** The ID of the Lobby. The ID is immutable. */
	FName Id;
	/**
	 * The list of players.
	 * 
	 * Always has a space for 4 elements. And contains at least one player. Ohterwise
	 * there would be no Lobby.
	 */
	TStaticArray<USchafkopfPlayer*, 4> Players;
	/**
	 * The amount of players in the Lobby.
	 * 
	 * There is at least 1 player and a maximum of 4 players in the Lobby.
	 */
	uint8 PlayerCount;
	
public:
	/**
	 * Returns the ID of the Lobby.
	 * 
	 * The ID of the Lobby is immutable.
	 * 
	 * @return The ID of the Lobby.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetId();

	/**
	 * Returns the amount of players in the Lobby.
	 * 
	 * There is at least 1 player and a maximum of 4 players in the Lobby.
	 * 
	 * @return The amount of players in the Lobby.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	uint8 GetPlayerCount() const;

	/**
	 * Returns the player specified by the ID.
	 * 
	 * @param PlayerId - The ID of the player.
	 * @return A pointer to the player or a nullptr if no player could be
	 *		found by the specified ID.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USchafkopfPlayer* GetPlayer(const FName PlayerId) const;

	/**
	 * Returns the order of the player specified by the ID.
	 *
	 * @param PlayerId - The ID of the player.
	 * @return The order of the player or `-1` if no player could be
	 *		found by the specified ID.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetPlayerOrder(const FName PlayerId) const;

	/**
	 * Returns whether a player can be added to the Lobby.
	 * 
	 * @return `true` if and only if a player can be added.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanAddPlayer() const;

	/**
	 * Adds a new player to the Lobby.
	 * 
	 * @param Player - The new player to add.
	 */
	UFUNCTION(BlueprintCallable)
	void AddPlayer(USchafkopfPlayer* Player);

	/**
	 * Removes a player from the Lobby.
	 * 
	 * @param Player - The player to remove.
	 */
	UFUNCTION(BlueprintCallable)
	void RemovePlayer(USchafkopfPlayer* Player);

	/**
	 * Creates a new Lobby.
	 * 
	 * @param Id - The ID of the Lobby.
	 * @return A new Lobby object.
	 */
	UFUNCTION(BlueprintCallable)
	static USchafkopfLobby* Make(const FName Id);
};
