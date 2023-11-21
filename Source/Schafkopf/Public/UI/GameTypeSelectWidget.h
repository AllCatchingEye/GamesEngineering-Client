// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WsMessage.h"
#include "GameTypeSelectWidget.generated.h"

/**
 * The GameTypeSelectWidget class.
 */
UCLASS()
class SCHAFKOPF_API UGameTypeSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFields(const TArray<FWSGameTypeWithSuit>& Groups);
};
