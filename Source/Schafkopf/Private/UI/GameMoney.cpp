// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameMoney.h"
#include <Core/SchafkopfPlayerController.h>

void UGameMoney::UpdateMoneyUI()
{
	auto controller = Cast<ASchafkopfPlayerController>(GetWorld()->GetFirstPlayerController());
	
	int money = controller->GetPosessedPawn()->GetMoney();

	int euro = money / 100;
	int cents = money % 100;
	this->moneyUI = FString::Printf(TEXT("%d euros and %d cents"), euro, cents);
}
