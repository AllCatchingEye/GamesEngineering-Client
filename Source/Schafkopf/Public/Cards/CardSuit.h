// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardSuit.generated.h"

/**
 * The CardSuit enum.
 * 
 * Provides a list of all available suits, that a card may have.
 * 
 * The value of `NONE` is used exclusively in cases where a client
 * should not be aware of the actual card. For example: Any cards
 * that are in the hand of another player should not be known to
 * the current player. The server obviously always knows about all
 * cards, and thus does not need the `NONE` value.
 */
UENUM(BlueprintType)
enum class ECardSuit : uint8
{
	NONE = 0		UMETA(DisplayName = "NONE"),
	EICHEL = 1		UMETA(DispalyName = "EICHEL"),
	GRAS = 2		UMETA(DispalyName = "GRAS"),
	HERZ = 3		UMETA(DispalyName = "HERZ"),
	SCHELLEN = 4	UMETA(DispalyName = "SCHELLEN")
};

ECardSuit GetCardSuitFromString(const FString& SuitString)
{
    UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECardSuit"), true);
    if (!EnumPtr)
    {
        // Handle error: Unable to find the enum
        return ECardSuit::NONE;
    }

    return (ECardSuit)EnumPtr->GetValueByNameString(*SuitString);
}

ENUM_RANGE_BY_FIRST_AND_LAST(ECardSuit, ECardSuit::EICHEL, ECardSuit::SCHELLEN);
