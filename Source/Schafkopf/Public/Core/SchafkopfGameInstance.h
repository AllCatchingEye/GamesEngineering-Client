// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "IWebSocket.h"
#include "IWebSocketsManager.h"
#include "WebSocketsModule.h"

#include "SchafkopfGameInstance.generated.h"

/**
 * The SchafkopfGameInstance class.
 * 
 * The SchafkopfGameInstance represents the instance of the running game.
 * It is spawned at game creation and not destroyed until the game instance
 * is shut down. There can only be one game instance present.
 */
UCLASS()
class SCHAFKOPF_API USchafkopfGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	/** The name of the WebSocket module. */
	static const char* WEB_SOCKET_MODULE;
	/** The address of the WebSocket. */
	static const char* WEB_SOCKET_ADDRESS;
	/** The protocol of the WebSocket. */
	static const char* WEB_SOCKET_PROTOCOL;

	/** The pointer to the WebSocket. */
	TSharedPtr<IWebSocket> WebSocket = nullptr;

public:
	//Called upon shutdown of the game. Handle final cleanup here.
	virtual void Shutdown() override;

	/** Opens a WebSocket connection to the server. */
	UFUNCTION()
	void WebSocketConnect();
	/** Closes a WebSocket connection to the server. */
	UFUNCTION()
	void WebSocketDisconnect();

protected:
	/** Called when a WebSocket connection has been established successfully. */
	UFUNCTION()
	void OnWebSocketConnected();
	/**
	 * Called when a WebSocket connection could not be established.
	 * 
	 * @param Error The error message.
	 */
	UFUNCTION()
	void OnWebSocketConnectionError(const FString& Error);
	/**
	 * Called when a WebSocket connection has been closed.
	 * 
	 * @param StatusCode The status code.
	 * @param Reason The reason why the connection was closed.
	 * @param bWasClean Whether the connection was closed cleanly.
	 */
	UFUNCTION()
	void OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	/**
	 * Called when a WebSocket has received a text message.
	 * 
	 * @param Message The received text message.
	 */
	UFUNCTION()
	void OnWebSocketMessageReceived(const FString& Message);
};
