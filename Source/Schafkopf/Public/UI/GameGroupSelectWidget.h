// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"

#include "GameGroupSelectWidget.generated.h"

/**
 * The GameGroupSelectWidget class.
 */
UCLASS()
class SCHAFKOPF_API UGameGroupSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFields(const TArray<FString>& Groups);

protected:
	UPROPERTY(BlueprintReadOnly)
	UVerticalBox* VerticalBox;
};
