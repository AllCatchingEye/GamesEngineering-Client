// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core/SchafkopfPlayer.h"
#include "PlayerOwnable.generated.h"

// Unreal Engine interfaces consist of two parts:
// 1. The class extending `UInterface`.
//    This class exists to make the interface visible to Unreal's reflection
//    system. It only contains the `GENERATED_BODY()` macro.
// 2. The actual interface class.
//	  This class holds the actual method definitions.

/**
 * The PlayerOwnable interface.
 */
UINTERFACE(BlueprintType, Blueprintable, Category = "Cards")
class SCHAFKOPF_API UPlayerOwnable : public UInterface
{
	GENERATED_BODY()
};

class SCHAFKOPF_API IPlayerOwnable
{
	GENERATED_BODY()

public:
	/**
	 * Returns whether this object is owned by a player.
	 *
	 * @return `true` if and only if it is owned by a player.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool HasOwner() const;

	/**
	 * Returns the owner of this object.
	 *
	 * @return The owner of this object.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	USchafkopfPlayer* GetOwner() const;

	/**
	 * Sets the owner of this object.
	 *
	 * The owner of an object can only be set once.
	 *
	 * @param NewOwner - The new owner.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	void SetOwner(USchafkopfPlayer* NewOwner);
};
