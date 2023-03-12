// Copyright Epic Games, Inc. All Rights Reserved.

#include "AT_UE5_OWLSGameMode.h"
#include "AT_UE5_OWLSCharacter.h"
#include "GreedyChunk.h"
#include "UObject/ConstructorHelpers.h"

AAT_UE5_OWLSGameMode::AAT_UE5_OWLSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}


	
}

void AAT_UE5_OWLSGameMode::WriteSave()
{
	
}


