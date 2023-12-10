// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

/**
 * The `GameHUD` class.
 * 
 * This widget is used to display persistent information.
 */
UCLASS()
class SCHAFKOPF_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateMoney(int32 NewMoney);

	void UpdateGameType(FText NewGameType);

protected:
	UPROPERTY(BlueprintReadOnly)
	FText Money;

	UPROPERTY(BlueprintReadOnly)
	FText GameType;
};
