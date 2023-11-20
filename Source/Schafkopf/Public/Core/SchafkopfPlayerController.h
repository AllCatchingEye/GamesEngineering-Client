// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Core/SchafkopfCharacter.h"
#include "SchafkopfPlayerController.generated.h"

/**
 * The SchafkopfPlayerController class.
 */
UCLASS(BlueprintType)
class SCHAFKOPF_API ASchafkopfPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASchafkopfPlayerController();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY()
	UUserWidget* WidgetInstance;

private:
	ASchafkopfCharacter* PosessedPawn;
};
