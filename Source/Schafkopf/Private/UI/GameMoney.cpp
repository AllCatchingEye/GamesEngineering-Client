// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameMoney.h"
#include <Core/SchafkopfPlayerController.h>

void UGameMoney::UpdateMoneyUI()
{
	auto controller = GetWorld()->GetFirstPlayerController();

	if (controller != nullptr) {
		auto playerController = Cast<ASchafkopfPlayerController>(controller);

		int money = playerController->GetPosessedPawn()->GetMoney();
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::White, FString::Printf(TEXT("Money of player: %d"), money));

		int euro = money / 100;
		int cents = money % 100;
		this->moneyUI = FString::Printf(TEXT("%d euros and %d cents"), euro, cents);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::White, FString::Printf(TEXT("Euro, Cents: %d, %d"), euro, cents));
	}
}
