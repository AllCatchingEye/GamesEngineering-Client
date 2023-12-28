// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WSMessage.h"

#include "Cards/CardSuit.h"
#include "Cards/CardRank.h"

#include "JsonUtilities.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// START - Helper functions																		//
//////////////////////////////////////////////////////////////////////////////////////////////////

FString GetJsonMessageId(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	FString MessageId;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		JsonObject->TryGetStringField(TEXT("id"), MessageId);
	}

	if (MessageId.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE, 50.0f, FColor::Red,
			TEXT("Failed to get message id from JSON string.")
		);
	}

	return MessageId;
}

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

ECardRank GetCardRankFromString(const FString& RankString)
{
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECardRank"), true);
	if (!EnumPtr)
	{
		// Handle error: Unable to find the enum
		return ECardRank::NONE;
	}

	return (ECardRank)EnumPtr->GetValueByNameString(*RankString);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END - Helper functions																		//
//////////////////////////////////////////////////////////////////////////////////////////////////
