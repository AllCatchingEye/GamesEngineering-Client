// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/GameWinnerWidget.h"

#include "SKPlayerController.generated.h"

/**
 * The ASKPlayerController class.
 */
UCLASS(BlueprintType, Blueprintable)
class SCHAFKOPF_API ASKPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASKPlayerController();

	virtual void BeginPlay() override;

	/**
	 * Returns the pawn that the player posesses and controls.
	 * 
	 * @return The pawn that the player posesses and controls.
	 */
	class ASKCharacter* GetPosessedPawn();

	/** Shows the GameHUD widget. */
	void AddWidgetGameHUD();

	/** Shows the GameHUD widget. */
	void HideGameHUD();

	void ShowGameHUD();

	/**
	 * Updates the money of the GameHUD.
	 * 
	 * @param NewMoney - The new amount of money.
	 */
	void UpdateWidgetGameHUDMoney(int32 NewMoney);

	/**
	 * Updates the game type of the GameHUD.
	 *
	 * @param NewGameType - The new game type.
	 */
	void UpdateWidgetGameHUDGameType(const FText NewGameType);



	/** Shows the WantsToPlay widget. */
	void ShowWidgetWantsToPlay();

	/**
	 * Shows the GameGroupSelect widget.
	 *
	 * @param Groups - The available groups.
	 */
	void ShowWidgetGameGroupSelect(const TArray<FString> Groups);

	void ClearGameTypeSelect();

	void ClearGameGroupSelect();

	/**
	 * Shows the GameTypeSelect widget.
	 *
	 * @param Types - The available types.
	 */
	void ShowWidgetGameTypeSelect(const TArray<struct FWSGameTypeWithSuit> Types);

	virtual void SetupInputComponent() override;

	void OnLeftMouseButtonPressed();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Schafkopf|UI")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Schafkopf|UI")
	TSubclassOf<class UGameHUD> WidgetClassGameHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Schafkopf|UI")
	TSubclassOf<UUserWidget> WidgetClassWantsToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Schafkopf|UI")
	TSubclassOf<class UGameGroupSelectWidget> WidgetClassGameGroupSelect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Schafkopf|UI")
	TSubclassOf<class UGameTypeSelectWidget> WidgetClassGameTypeSelect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Schafkopf|UI")
	TSubclassOf<class UGameWinnerWidget> WidgetClassGameWinner;

	UPROPERTY(Blueprintreadwrite)
	class UGameHUD* WidgetInstanceGameHUD;
	
private:
	/** The pawn that the player posesses and controls. */
	class ASKCharacter* PosessedPawn;

	UPROPERTY()
	UUserWidget* WidgetInstance;



	UPROPERTY()
	UUserWidget* WidgetInstanceWantsToPlay;

	UPROPERTY()
	class UGameGroupSelectWidget* WidgetInstanceGameGroupSelect;

	UPROPERTY()
	class UGameTypeSelectWidget* WidgetInstanceGameTypeSelect;


};
