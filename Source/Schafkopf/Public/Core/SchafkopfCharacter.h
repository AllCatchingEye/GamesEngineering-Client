// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineComponent.h"
#include "SchafkopfPlayer.h"
#include "SchafkopfCharacter.generated.h"

UCLASS()
class SCHAFKOPF_API ASchafkopfCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASchafkopfCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** The backing player. */
	USchafkopfPlayer* Player = nullptr;
	/** The spline along which the cards will be arranged. */
	USplineComponent* CardSpline = nullptr;
};
