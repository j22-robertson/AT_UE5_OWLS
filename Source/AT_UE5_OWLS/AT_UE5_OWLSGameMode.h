// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GreedyChunk.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/SaveGame.h"
#include "AT_UE5_OWLSGameMode.generated.h"

UCLASS(minimalapi)
class AAT_UE5_OWLSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAT_UE5_OWLSGameMode();

	void WriteSave();
	
	UPROPERTY(EditAnywhere, Category="Chunk World")
	TSubclassOf<AActor> Chunk;
	UPROPERTY(EditAnywhere)
	int DrawDistance = 5;

	UPROPERTY(EditAnywhere)
	int ChunkSize = 32;
//	UPROPERTY()
	//USaveGame* SaveGame;
};



