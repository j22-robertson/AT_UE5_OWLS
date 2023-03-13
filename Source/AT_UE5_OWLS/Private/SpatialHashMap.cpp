// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialHashMap.h"

#include "Debug/ReporterGraph.h"


USpatialHashMap::USpatialHashMap()
{
	inverseWorldToGrid = 0.0003125;//1.0/(100.0/32.0);
}

TArray<AActor*> USpatialHashMap::GetActorsInCell(const FVector& Position) const
{
	FVector2D cellpos = FVector2D{Position.X, Position.Y}* inverseWorldToGrid;
	FIntVector2 hashkey = FIntVector2((int32)cellpos.X,(int32)cellpos.Y);
	return GridCells[hashkey];
}

void USpatialHashMap::AddActor(AActor* Actor)
{
	
	const FVector& ActorPosition = Actor->GetActorLocation();
	FIntVector2 hashkey = FIntVector2((int32)ActorPosition.X* 0.0003125,(int32)ActorPosition.Y* 0.0003125);
	
	if(!GridCells.Contains(hashkey))
	{
		GridCells.Add(hashkey, TArray<AActor*>());
	}
	GridCells[hashkey].Add(Actor);
		

		
		
}

void USpatialHashMap::RemoveActor(AActor* Actor)
{
	const FVector& ActorPosition = Actor->GetActorLocation()/100/CellSize;
	FIntVector2 hashkey = FIntVector2((int32)ActorPosition.X,(int32)ActorPosition.Y);


		
}

