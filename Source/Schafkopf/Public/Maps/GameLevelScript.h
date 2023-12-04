// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "GameLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class SCHAFKOPF_API AGameLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetPlayerIds(const TArray<FString>& playerIds);

	UFUNCTION(BlueprintImplementableEvent)
	void RoundEnd(const FString& winnerID);

	UFUNCTION(BlueprintImplementableEvent)
	void GameEnd(const TArray<FString>& playerIds);
};
