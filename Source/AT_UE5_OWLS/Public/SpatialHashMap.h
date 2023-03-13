// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "SpatialHashMap.generated.h"

/**
 * 
 */

UCLASS()
class AT_UE5_OWLS_API USpatialHashMap : public UObject
{
	GENERATED_BODY()
public:

	USpatialHashMap();
	TArray<AActor*> GetActorsInCell(const FVector& Position) const;

	
	void AddActor(AActor* Actor);
	void RemoveActor(AActor* Actor);
	TMap<FIntVector2, TArray<AActor*>> GridCells;
	float inverseWorldToGrid;
private:
	//TMap<FIntVector2, TArray<AActor*>> GridCells;
	
	UPROPERTY(EditAnywhere, Category="Hashmap Settings")
	int CellSize = 32;
	
};
