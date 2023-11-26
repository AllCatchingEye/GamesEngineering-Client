// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SchafkopfPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SCHAFKOPF_API USchafkopfPlayer : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Returns the ID of the Player.
	 *
	 * The ID of the Player is immutable.
	 *
	 * @return The ID of the Player.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetId();

	/**
	 * Creates a new Player.
	 *
	 * @param Id - The ID of the Player.
	 * @return A new Player object.
	 */
	UFUNCTION(BlueprintCallable)
	static USchafkopfPlayer* Make(const FName Id);

private:
	/** The ID of the Player. The ID is immutable. */
	FName Id;
};
