// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums.h"
#include "Public/ChunkMeshData.h"
#include "GreedyChunk.generated.h"


class UProceduralMeshComponent;
class FastNoiseLite;
struct FChunkMeshData;
enum class BlockType : uint8;

UCLASS()
class AT_UE5_OWLS_API AGreedyChunk : public AActor
{
	GENERATED_BODY()
	struct FMask
	{
		BlockType Block;
		int Normal;
	};
	FBufferArchive ToBinary;

	
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
	UFUNCTION(BlueprintCallable, Category="GreedyChunk")
	void EditChunk(const FIntVector position, const BlockType block);
	
	void ClearMesh();
	void EditChunkMesh(const FIntVector position,BlockType block);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
UPROPERTY()
	TArray<BlockType> Blocks;
	
	FChunkMeshData MeshData;
protected:
	
private:
	TObjectPtr<UProceduralMeshComponent> Mesh = nullptr;
	TObjectPtr<FastNoiseLite> Noise = nullptr;

	int vertcount = 0;




	void GenerateBlocks();
	void GenerateMesh();
	void ApplyMesh() const;

	
	
	//TArray<BlockType> blocks;
	
	


	int GetBlockIndex(int x, int y, int z) const;

	void CreateQuad(FMask Mask, FIntVector AxisMask, FIntVector V1, FIntVector V2, FIntVector V3, FIntVector V4);

	BlockType GetBlock(FIntVector Index) const;

	bool CompareMask(FMask M1, FMask M2) const;
};

FORCEINLINE FArchive &operator <<(FArchive &Ar, AGreedyChunk& ChunkData )
{
	//Ar << ChunkData.MeshData;
	//Ar << TheStruct.DamageAmount;
	//Ar << TheStruct.HitLocation;
	//Ar << TheStruct.ImpulseDir;
	//Ar << TheStruct.ImpulseStrength;
	
	return Ar;
}