// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"

#include "Core/SKGameInstance.h"
#include "MainMenuLevel.generated.h"

/**
 * The MainMenuLevel class.
 */
UCLASS()
class SCHAFKOPF_API AMainMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AMainMenuLevel();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void SetLink(const FString& Link);

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void SetBots(const TArray<FString>& BotList);

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void SetHumans(int32 HumanCount);

protected:

private:
	/** The GameInstance. */
	USKGameInstance* GameInstance;
};
