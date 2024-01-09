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
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> playerIds;

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> gameWinner;

	UPROPERTY(BlueprintReadWrite)
	FString roundWinner;

	void SetPlayerIDs(TArray<FString> playerIds);

	void SetRoundWinner(FString winnerID);

	void SetGameWinners(TArray<FString> playerIds);

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void AssignPlayerIDs();

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void RoundEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void GameEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void ShowAction(const FString& action, const FString& playerID);

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void ShowGameWinner(bool isWinner, int32 Points);

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void StartDelay(const int32& Seconds);

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void SetOrder(const TMap<FString, int32>& Orders) ;

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void SetCard(const FString& Ref, const FText& Card);

	UFUNCTION(BlueprintImplementableEvent, Category = "Schafkopf")
	void SetTurn(const FString& Ref);
};
