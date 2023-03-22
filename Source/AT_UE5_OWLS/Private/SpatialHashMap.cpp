// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialHashMap.h"




FSpatialHashMap::FSpatialHashMap()
{
	//GridCells = TMap<FIntVector2, TArray<AActor*>>();
	inverseWorldToGrid = 1.0/100/32;
}

TArray<AActor*> FSpatialHashMap::GetActorsInCell(const FVector3f& Position) const
{
	FIntVector IPosition = static_cast<FIntVector>(static_cast<FVector>(Position));
	FIntVector ChunkPosition  = static_cast<FIntVector>(IPosition * inverseWorldToGrid);
	

	FIntVector2 key;
	if(IPosition.X < 0)
	{
		key.X=ChunkPosition.X-1;
	}
	else
	{
		key.X = ChunkPosition.X;
	}
	if(IPosition.Y < 0)
	{
		key.Y=ChunkPosition.Y-1;
	}
	else
	{
		key.Y = ChunkPosition.Y;
	}
	
	//const FIntVector2& key = FIntVector2(static_cast<int32>(Position.X* inverseWorldToGrid)+5,static_cast<int32>(Position.Y* inverseWorldToGrid)+5);
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

	FIntVector IPosition = static_cast<FIntVector>(ActorPosition );
	FIntVector ChunkPosition  = static_cast<FIntVector>(IPosition * inverseWorldToGrid);

	FIntVector2 key;
	if(ActorPosition.X < 0)
	{
		key.X=ChunkPosition.X-1;
	}
	else
	{
		key.X = ChunkPosition.X;
	}
	if(ActorPosition.Y < 0)
	{
		key.Y=ChunkPosition.Y-1;
	}
	else
	{
		key.Y =ChunkPosition.Y;
	}
	
	//const FIntVector2& key = FIntVector2(static_cast<int32>(ActorPosition.X* inverseWorldToGrid)+5,static_cast<int32>(ActorPosition.Y* inverseWorldToGrid)+5);
	//uint32 hashkey = GetTypeHash(key);

	
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

