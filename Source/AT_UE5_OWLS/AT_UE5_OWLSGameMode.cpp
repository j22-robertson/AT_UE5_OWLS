// Copyright Epic Games, Inc. All Rights Reserved.

#include "AT_UE5_OWLSGameMode.h"
#include "AT_UE5_OWLSCharacter.h"
#include "GreedyChunk.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UnrealTypePrivate.h"

AAT_UE5_OWLSGameMode::AAT_UE5_OWLSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	for(int x = -DrawDistance; x <= DrawDistance; ++x)
	{
		for(int y = -DrawDistance; y <= DrawDistance; ++y)
		{
    			
			//GetWorld()->SpawnActor<AActor>(Chunk, FVector(x *ChunkSize * 100, y*ChunkSize*100,0), FRotator::ZeroRotator);
			//GetWorld()->GetSubsystem<>()
			/*
		if(!GridCells.Contains(hashkey) && spawnedActor != nullptr)
		{
			GridCells.Add(hashkey, TArray<AActor*>());
		}
		GridCells[hashkey].Add(spawnedActor);*/
			
		}
	}
	


	
}

void AAT_UE5_OWLSGameMode::WriteSave()
{
	
}


