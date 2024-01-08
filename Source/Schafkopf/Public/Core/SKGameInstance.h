// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "SKGameInstance.generated.h"

/**
 * The SKGameInstance class.
 *
 * The SKGameInstance represents the instance of the running game. It is spawned at game creation
 * and not destroyed until the game instance is shut down. There can only be one game instance,
 * so it is essentially a singleton.
 *
 * The game itself is separate from the Server and mainly exists as a graphical interface for the
 * user. The Client only knows about a limited subset of the actual game state and only implements
 * basic logic, without knowing about the rules of Schafkopf. For mor information visit the wiki.
 */
UCLASS()
class SCHAFKOPF_API USKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Called upon start of the game. Handle initial setup here.
	virtual void Init() override;

	// Called upon shutdown of the game. Handle final cleanup here.
	virtual void Shutdown() override;

	/* Start a singleplayer level */
	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	virtual void StartSingleplayer();

	class ASKPlayerController* GetController();

private:
	/** The name of the WebSocket module. */
	const wchar_t* WEB_SOCKET_MODULE = TEXT("WebSockets");
	/** Teh name of the main menu level. */
	const wchar_t* LEVEL_NAME_MAINMENU = TEXT("MainMenuLevel");
	/** The name of the ingame level. */
	const wchar_t* LEVEL_NAME_INGAME = TEXT("GameLevel");

	/** The default address of the WebSocket. */
	FString WEB_SOCKET_ADDRESS = TEXT("ws://schafkopfen.duckdns.org");
	/** The default protocol of the WebSocket. */
	const wchar_t* WEB_SOCKET_PROTOCOL = TEXT("ws");

	ALevelScriptActor* LevelScriptActor = nullptr;

	bool hasConnected = false;

	/** The pointer to the WebSocket. */
	TSharedPtr<class IWebSocket> WebSocket = nullptr;

	/** The ID of the player. */
	FString PlayerId;
	/** The local player. There is only one player. */
	class ASKPlayerController* PlayerController;
	/** The current card trick. */
	class ACardTrick* CardTrick;

	/** The current card trick. */
	class ACardTrick* prevCardTrick = nullptr;

	/** An array of all card tricks. There will be eight in total. */
	TArray<class ACardTrick*> CardTricks;

	//////////////////////////////////////////////////////////////////////////////////////////////
	// START - WebSockets																		//
	//////////////////////////////////////////////////////////////////////////////////////////////

public:
	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	void SetServerUrl(FString url);

	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	bool GetConnected();

	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	ACardTrick* GetCardTrick();

	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	void SetLevel(ALevelScriptActor* levelScriptActor);

	/** Opens a WebSocket connection to the server. */
	UFUNCTION()
	void WebSocketConnect();
	

	/** Closes a WebSocket connection to the server. */
	UFUNCTION()
	void WebSocketDisconnect();

	/** Called when a WebSocket connection has been established successfully. */
	UFUNCTION()
	void OnWebSocketConnected();

	/**
	 * Called when a WebSocket connection could not be established.
	 *
	 * @param Error - The error message.
	 */
	UFUNCTION()
	void OnWebSocketConnectionError(const FString& Error);

	/**
	 * Called when a WebSocket connection has been closed.
	 *
	 * @param StatusCode The status code.
	 * @param Reason - The reason why the connection was closed.
	 * @param bWasClean - Whether the connection was closed cleanly.
	 */
	UFUNCTION()
	void OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean);

	/**
	 * Called when a WebSocket has received a text message.
	 *
	 * @param Message - The received text message.
	 */
	UFUNCTION()
	void OnWebSocketMessageReceived(const FString& Message);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// END - WebSockets																			//
	//																							//
	// START - Lobby																			//
	//////////////////////////////////////////////////////////////////////////////////////////////

private:

	//////////////////////////////////////////////////////////////////////////////////////////////
	// END - Lobby																				//
	//																							//
	// START - Ingame																			//
	//////////////////////////////////////////////////////////////////////////////////////////////

private:
	/** Called upon the start of the game. */
	void OnGameStartUpdate(const FString& Message);

	void OnPlayDecisionUpdate(const FString& Message);

	/** Called upon the start of a round. */
	void OnPlayOrderUpdate(const FString& Message); // TODO: Rename to OnRoundStartUpdate(...).

	/** Called upon the end of a round. */
	void OnRoundResultUpdate(const FString& Message); // TODO: Rename to OnRoundEndUpdate(...).

	/** Called upon the end of the game. */
	void OnGameEndUpdate(const FString& Message);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// START - Ingame - Queries																	//
	//////////////////////////////////////////////////////////////////////////////////////////////

private:
	/** Called when the server queries the client for the player's play decision. */
	void OnPlayerWantsToPlayQuery(const FString& Message);

	/** Called when the server queries the client for the player's game group decision. */
	void OnPlayerSelectGameGroupQuery(const FString& Message);

	/** Called when the server queries the client for the player's game type decision. */
	void OnPlayerSelectGameTypeQuery(const FString& Message);

	/** Called when the server queries the client for the player's card selection. */
	void OnPlayerPlayCardQuery(const FString& Message);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// END - Ingame - Queries																	//
	//																							//
	// START - Ingame - Query Updates															//
	//////////////////////////////////////////////////////////////////////////////////////////////

private:
	/**  */
	void OnGameGroupSelectedUpdate(const FString& Message);

	/**  */
	void OnGameTypeSelectedUpdate(const FString& Message);

	/**  */
	void OnCardPlayedUpdate(const FString& Message);

	/**  */
	void OnGameMoneyUpdate(const FString& Message);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// END - Ingame - Query Updates																//
	//																							//
	// START - Ingame - Notify server															//
	//////////////////////////////////////////////////////////////////////////////////////////////

public:
	/**
	 * Notifies the server whether the user wants to play.
	 *
	 * @param WantsToPlay - whether the user wants to play
	 */
	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	void SendWantsToPlay(const bool WantsToPlay);

	/**
	 * Notifies the server what game group the user selected.
	 *
	 * @param GameGroupIndex - The index of the game group
	 */
	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	void SendGameGroupSelect(const int32 GameGroupIndex);

	/**
	 * Notifies the server what game type the user selected.
	 *
	 * @param GameTypeIndex - The index of the game type
	 */
	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	void SendGameTypeSelect(const int32 GameTypeIndex);

	/**
	 * Notifies the server what card the user selected.
	 *
	 * @param CardIndex - The index of the card
	 */
	UFUNCTION(BlueprintCallable, Category = "Schafkopf")
	void SendCardPlay(const int32 CardIndex);

	//////////////////////////////////////////////////////////////////////////////////////////////
	// END - Ingame - Notify server																//
	// END - Ingame																				//
	//////////////////////////////////////////////////////////////////////////////////////////////
};
