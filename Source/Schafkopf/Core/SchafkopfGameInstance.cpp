// Fill out your copyright notice in the Description page of Project Settings.


#include "SchafkopfGameInstance.h"

void USchafkopfGameInstance::Shutdown() {
	WebSocketDisconnect();
	Super::Shutdown();
}

void USchafkopfGameInstance::WebSocketConnect() {
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		FModuleManager::Get().LoadModule("WebSockets");
	}

	//TODO: Change to `wss` protocol in Development.
	//The current protocol is unencrypted.
	WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://ADD_IP_ADDRESS_HERE");

	WebSocket->Connect();
}

void USchafkopfGameInstance::WebSocketDisconnect() {
	if (WebSocket && WebSocket->IsConnected()) {
		WebSocket->Close();
	}
}
