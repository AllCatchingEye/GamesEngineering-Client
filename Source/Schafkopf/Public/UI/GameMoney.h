// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMoney.generated.h"

/**
 * 
 */
UCLASS()
class SCHAFKOPF_API UGameMoney : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateMoneyUI();
	
private:
	int moneyUI;
};
