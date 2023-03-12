// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/BufferArchive.h"
#include "ChunkMeshData.generated.h"

USTRUCT()
struct FChunkMeshData 
{
	GENERATED_BODY()
	public:
	UPROPERTY()
	TArray<FVector> Vertices;
	UPROPERTY()
	TArray<int> Triangles;
	UPROPERTY()
	TArray<FVector> Normals;
	UPROPERTY()
	TArray<FVector2D> UV0;
	
	void Clear();
};
FORCEINLINE FArchive &operator <<(FArchive &Ar, FChunkMeshData& MeshData )
{
	Ar << MeshData.Vertices;
	Ar << MeshData.Triangles;
	Ar << MeshData.Normals;
	Ar << MeshData.UV0;
	return Ar;
}