// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "SKCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SCHAFKOPF_API ASKCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASKCharacter();

	/**
	 * Returns the card hand of the player.
	 * 
	 * @return The card hand of the player.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class ACardHand* GetCardHand() const;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetMoney(int32 newMoney);

	int32 GetMoney();

protected:
	virtual void BeginPlay() override;

private:
	/** The hand cards of the player. */
	class ACardHand* CardHand;

	int32 money;
};
