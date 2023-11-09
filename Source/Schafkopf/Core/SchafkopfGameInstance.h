// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "IWebSocket.h"
#include "IWebSocketsManager.h"
#include "WebSocketsModule.h"

#include "SchafkopfGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SCHAFKOPF_API USchafkopfGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
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
};
