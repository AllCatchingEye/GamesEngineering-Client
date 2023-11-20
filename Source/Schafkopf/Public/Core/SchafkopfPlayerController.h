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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClassWantsToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClassGameGroupSelect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClassGameTypeSelect;

	UPROPERTY()
	UUserWidget* WidgetInstance;

	UPROPERTY()
	UUserWidget* WidgetInstanceWantsToPlay;

	UPROPERTY()
	UUserWidget* WidgetInstanceGameGroupSelect;

	UPROPERTY()
	UUserWidget* WidgetInstanceGameTypeSelect;

	/** Shows the WantsToPlay widget. */
	void ShowWidgetWantsToPlay();

	/**
	 * Shows the GameGroupSelect widget.
	 * 
	 * @param Groups - The available groups.
	 */
	void ShowWidgetGameGroupSelect(const TArray<FString> Groups);

	/**
	 * Shows the GameTypeSelect widget.
	 *
	 * @param Types - The available types.
	 */
	void ShowWidgetGameTypeSelect(const TArray<FString> Types);

private:
	ASchafkopfCharacter* PosessedPawn;
};
