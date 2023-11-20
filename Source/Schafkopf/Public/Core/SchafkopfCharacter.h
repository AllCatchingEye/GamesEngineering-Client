// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineComponent.h"

#include "Core/SchafkopfPlayer.h"
#include "Cards/Card.h"
#include "Cards/CardHand.h"

#include "SchafkopfCharacter.generated.h"

UCLASS()
class SCHAFKOPF_API ASchafkopfCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASchafkopfCharacter();

	/**
	 * Returns the backing player.
	 * 
	 * @return The backing player.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USchafkopfPlayer* GetPlayer();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACardHand* GetCardHand() const;

	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** The backing player. */
	USchafkopfPlayer* Player;
	/** The hand cards of the player. */
	ACardHand* CardHand;
};
