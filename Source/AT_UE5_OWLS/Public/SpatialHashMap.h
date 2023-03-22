// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "SpatialHashMap.generated.h"

/**
 * 
 */

USTRUCT()
struct FSpatialHashMap
{
	GENERATED_BODY()
public:
	FSpatialHashMap();
	TArray<AActor*> GetActorsInCell(const FVector3f& Position) const;
	TArray<AActor*>::TConstIterator GetActorsInCellByIndex(uint32 x, uint32 y) const;
	void AddActor(AActor& Actor);
	void RemoveActor(AActor* Actor);

	TMap<FIntVector2, TArray<AActor*>> GridCells;
	float inverseWorldToGrid;
private:
	//TMap<FIntVector2, TArray<AActor*>> GridCells;
	
	UPROPERTY(EditAnywhere, Category="Hashmap Settings")
	int CellSize = 32;
	
};
