// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialHashMap.h"




FSpatialHashMap::FSpatialHashMap()
{
	//GridCells = TMap<FIntVector2, TArray<AActor*>>();
	inverseWorldToGrid = 1.0/100/32;
}

TArray<AActor*> FSpatialHashMap::GetActorsInCell(const FVector& Position) const
{
	FVector2D cellpos = FVector2D{Position.X, Position.Y}* inverseWorldToGrid;
	FIntVector2 key = FIntVector2((int32)cellpos.X,(int32)cellpos.Y);

	uint32 hashkey = GetTypeHash(key);
	return GridCells[key];
}

TArray<AActor*>::TConstIterator FSpatialHashMap::GetActorsInCellByIndex(uint32 x, uint32 y) const
{
	//FVector2D cellpos = FVector2D{Position.X, Position.Y}* inverseWorldToGrid;
	FIntVector2 key = FIntVector2(x+5,y+5);

	//uint32 hashkey = GetTypeHash(key);
	return GridCells[key].CreateConstIterator();
}
void FSpatialHashMap::AddActor(AActor& Actor)
{
	
	const FVector& ActorPosition = Actor.GetActorLocation();
	//GetTypeHash(ActorPosition);
	
	const FIntVector2& key = FIntVector2(static_cast<int32>(ActorPosition.X* inverseWorldToGrid)+5,static_cast<int32>(ActorPosition.Y* inverseWorldToGrid)+5);
	uint32 hashkey = GetTypeHash(key);

	
	if(!GridCells.Contains(key))
	{
		GridCells.Add(key, TArray<AActor*>());
	}

		GridCells[key].Add(&Actor);
	
		

		
		
}

void FSpatialHashMap::RemoveActor(AActor* Actor)
{
	const FVector& ActorPosition = Actor->GetActorLocation()/100/CellSize;
	FIntVector2 hashkey = FIntVector2((int32)ActorPosition.X,(int32)ActorPosition.Y);


		
}

