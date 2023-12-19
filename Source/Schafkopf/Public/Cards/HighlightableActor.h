// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HighlightableActor.generated.h"

// Unreal Engine interfaces consist of two parts:
// 1. The class extending `UInterface`.
//    This class exists to make the interface visible to Unreal's reflection
//    system. It only contains the `GENERATED_BODY()` macro.
// 2. The actual interface class.
//	  This class holds the actual method definitions.

/**
 * The HighlightableActor interface.
 */
UINTERFACE(BlueprintType, Blueprintable, Category = "Cards")
class SCHAFKOPF_API UHighlightableActor : public UInterface
{
	GENERATED_BODY()
};

class SCHAFKOPF_API IHighlightableActor
{
	GENERATED_BODY()

public:
	/**
	 * Returns whether this actor is highligted.
	 *
	 * @return `true` if and only if the actor is highligted.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	bool IsHighlighted() const;

	/**
	 * Sets whether this actor is highligted.
	 *
	 * @param bShouldBeHighlighted - `true` if and only if the actor should be highligted.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cards")
	void SetHighlighted(bool bShouldBeHighlighted);
};
