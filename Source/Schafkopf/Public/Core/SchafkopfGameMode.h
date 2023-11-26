// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Cards/CardTrick.h"
#include "SchafkopfGameMode.generated.h"

/**
 * The SchafkopfGameMode class.
 */
UCLASS()
class SCHAFKOPF_API ASchafkopfGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASchafkopfGameMode();

	ACardTrick* GetTickCurrent();
	// 15:15 - 16:50

private:
	/** The current trick. */
	ACardTrick* TrickCurrent;
};
