// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SchafkopfGameInstance.h"

const char* USchafkopfGameInstance::WEB_SOCKET_MODULE = "WebSockets";
const char* USchafkopfGameInstance::WEB_SOCKET_ADDRESS = "ws://ADD_IP_ADDRESS_HERE:AND_PORT";
const char* USchafkopfGameInstance::WEB_SOCKET_PROTOCOL = "ws";

void USchafkopfGameInstance::Shutdown()
{
	WebSocketDisconnect();
	Super::Shutdown();
}

void USchafkopfGameInstance::WebSocketConnect()
{
	if (!FModuleManager::Get().IsModuleLoaded(WEB_SOCKET_MODULE))
	{
		FModuleManager::Get().LoadModule(WEB_SOCKET_MODULE);
	}

	//TODO: Change to `wss` protocol in Production.
	//The current protocol is unencrypted.
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(WEB_SOCKET_ADDRESS, WEB_SOCKET_PROTOCOL);

	//Register event handlers.
	WebSocket->OnConnected().AddUFunction(this, FName("OnWebSocketConnected"));
	WebSocket->OnConnectionError().AddUFunction(this, FName("OnWebSocketConnectionError"));
	WebSocket->OnClosed().AddUFunction(this, FName("OnWebSocketClosed"));
	WebSocket->OnMessage().AddUFunction(this, FName("OnWebSocketMessageReceived"));

	WebSocket->Connect();
}

void USchafkopfGameInstance::WebSocketDisconnect()
{
	if (WebSocket && WebSocket->IsConnected())
	{
		WebSocket->Close();
	}
}

void USchafkopfGameInstance::OnWebSocketConnected()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, "Successfully connected.");
}

void USchafkopfGameInstance::OnWebSocketConnectionError(const FString& Error)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, Error);
}

void USchafkopfGameInstance::OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, bWasClean ? FColor::Green : FColor::Red, Reason);
}

void USchafkopfGameInstance::OnWebSocketMessageReceived(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Yellow, Message);
}
