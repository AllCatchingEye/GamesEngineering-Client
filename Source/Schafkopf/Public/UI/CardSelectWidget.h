// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "CardSelectWidget.generated.h"

/**
 * The UCardSelectWidget class.
 */
UCLASS()
class SCHAFKOPF_API UCardSelectWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFields(const TArray<struct FWSCard>& Cards);
};
