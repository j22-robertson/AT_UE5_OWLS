// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

class UProceduralMeshComponent;
class FastNoiseLite;
enum class BlockType : uint8;
UCLASS()
class AT_UE5_OWLS_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();
	

	UPROPERTY(EditAnywhere, Category="Chunk")
	int size = 32;

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

	TArray<FVector> vertexData;
	TArray<int> triangleData;
	TArray<FVector2d> UVData;

	TArray<BlockType> Blocks;

	int vertexCount = 0;

	const FVector BlockVertexData[8] =
		{FVector{100,100,100},
		FVector{100,0,100},
		FVector{100,0,0},
		FVector{100,100,0},
		FVector{0,0,100},
		FVector{0,100,100},
		FVector{0,100,0},
		FVector{0,0,0},
		};
	const int BlockTriangleData[24]
	{
		0,1,2,3,
		5,0,3,6,
		4,5,6,7,
		1,4,7,2,
		5,4,1,0,
		3,2,7,6
		
	};

	void GenerateBlocks();
	void GenerateMesh();
	void ApplyMesh() const;
	bool Check(FVector Position) const;

	void CreateFace( EDirection Direction, FVector Position);
	
	TArray<FVector> GetFaceVertices(EDirection Direction, FVector Position) const;
	FVector GetPositionInDirection(EDirection Direction, FVector Position);

	int GetBlockIndex(int x, int y, int z) const;

	
	

};
