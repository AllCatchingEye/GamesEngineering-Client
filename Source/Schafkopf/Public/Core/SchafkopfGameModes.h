// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SchafkopfGameModes.generated.h"

/**
 * The SchafkopfGameModes enum.
 * 
 * Provides a list of all available game modes, that user may select.
 * 
 * The value of `NONE` is used exclusively as escape value.
 */
UENUM(BlueprintType)
enum class ESchafkopfGameModes : uint8
{
	NONE = 0		UMETA(DisplayName = "NONE"),
	SINGLE = 1		UMETA(DisplayName = "SINGLE"),
	MULTI = 2		UMETA(DisplayName = "MULTI")
};

ENUM_RANGE_BY_FIRST_AND_LAST(ESchafkopfGameModes, ESchafkopfGameModes::SINGLE, ESchafkopfGameModes::MULTI);
