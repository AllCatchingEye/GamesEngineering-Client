// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWinnerWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCHAFKOPF_API UGameWinnerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFields(bool isWinner, int32 Points);
};
