// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChunkFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AT_UE5_OWLS_API UChunkFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category="Chunk")
	static FIntVector WorldToBlock(const FVector& position);

	UFUNCTION(BlueprintPure, Category="Chunk")
	static FIntVector WorldToLocalBlock(const FVector& position, const int size);
	
	UFUNCTION(BlueprintPure, Category="Chunk")
	static FIntVector WorldToChunk(const FVector& position, const int size);
};
