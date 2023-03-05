// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums.h"
#include "Public/ChunkMeshData.h"
#include "GreedyChunk.generated.h"


class UProceduralMeshComponent;
class FastNoiseLite;
enum class BlockType;

UCLASS()
class AT_UE5_OWLS_API AGreedyChunk : public AActor
{
	GENERATED_BODY()
	struct FMask
	{
		BlockType Block;
		int Normal;
	};
	


	
public:	
	// Sets default values for this actor's properties
	AGreedyChunk();
	UPROPERTY(EditAnywhere, Category="Chunk")
	FIntVector size = FIntVector(1,1,1)*32;

	UPROPERTY(EditAnywhere, Category="Chunk")
	int scale =1;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	TObjectPtr<UProceduralMeshComponent> Mesh = nullptr;
	TObjectPtr<FastNoiseLite> Noise = nullptr;

	int vertcount = 0;



	TArray<BlockType> Blocks;

	void GenerateBlocks();
	void GenerateMesh();
	void ApplyMesh() const;

	TObjectPtr<FChunkMeshData> MeshData;
	TArray<BlockType> blocks;
	
	


	int GetBlockIndex(int x, int y, int z) const;

	void CreateQuad(FMask Mask, FIntVector AxisMask, FIntVector V1, FIntVector V2, FIntVector V3, FIntVector V4);

	BlockType GetBlock(FIntVector Index) const;

	bool CompareMask(FMask M1, FMask M2) const;
};
