// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkFunctionLibrary.h"

FIntVector UChunkFunctionLibrary::WorldToBlock(const FVector& position)
{
	return FIntVector(position/100);
}

FIntVector UChunkFunctionLibrary::WorldToLocalBlock(const FVector& position, const int size)
{
	const FIntVector chunkPosition = WorldToChunk(position,size);
	FIntVector result = WorldToBlock(position) - chunkPosition*size;

	if(chunkPosition.X < 0) result.X--;
	if(chunkPosition.Y< 0) result.Y--;
	if(chunkPosition.Z < 0) result.Z--;
	return result;
}

FIntVector UChunkFunctionLibrary::WorldToChunk(const FVector& position, const int size)
{
	FIntVector result;
	const int factor =size*100;
	const FIntVector iposition = FIntVector(position);
	const FIntVector iScaledPosition =FIntVector(position/factor);
	if(iposition.X < 0)
	{
		result.X=iScaledPosition.X-1;
	}
	else
	{
		result.X = iScaledPosition.X;
	}
	if(iposition.Y < 0)
	{
		result.Y=iScaledPosition.Y-1;
	}
	else
	{
		result.Y = iScaledPosition.Y;
	}
	if(iposition.Z < 0)
	{
		result.Z=iScaledPosition.Z-1;
	}
	else
	{
		result.Z = iScaledPosition.Z;
	}


	
	return  result;
}
