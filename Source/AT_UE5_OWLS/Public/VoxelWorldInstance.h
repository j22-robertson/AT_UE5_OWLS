// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quadtree.h"
#include "SpatialHashMap.h"
#include "AT_UE5_OWLS/GreedyChunk.h"
#include "Engine/GameInstance.h"
#include "VoxelWorldInstance.generated.h"

/**
 * 
 */
UCLASS()
class AT_UE5_OWLS_API UVoxelWorldInstance : public UGameInstance
{
	GENERATED_BODY()
	UVoxelWorldInstance();
	//FSpatialHashMap hashmap;


	UFUNCTION(BlueprintCallable)
	void PrintStuff(int num);
	UFUNCTION(BlueprintCallable)
	void UpdateChunksLoaded(const FVector3f& transform);
	UFUNCTION(BlueprintCallable)
	void SpawnWorldTemp();
	UFUNCTION(BlueprintCallable)
	void QueryAndUnrender(FVector position, float area);
	
	void QueryChunksToLoad(Node& node, FVector posittion, const float& area);

	UFUNCTION(BlueprintCallable)
	void LoadChunks();
	
	UFUNCTION(BlueprintCallable)
	void UnloadChunks(FVector position, float area);

	TQueue<Node*> ChunksToLoad;

	TSet<Node*> ChunksLoaded;

	TArray<AActor*> Query(Node& node, FVector position, float area);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Chunk;
	UPROPERTY(EditAnywhere)
	int ChunkSize;
	UPROPERTY(EditAnywhere)
	int DrawScale;
	UPROPERTY(EditAnywhere)
	FText WorldName;
	int MaxDepth;
	
	Node* root;
	

	FQuadtree* Quadtree;
	//FQuadtree VoxelWorldTree =FQuadtree{FVector3f{0,0,0}, 1028, 50, 32 };;

	
public:
	void LoadData();
	
	
	void Register(AActor* actor);
	void Subdivide(Node& node);
	void SubdivMaxTest(Node& node);
	bool Intersects(Node& node, FVector position, float area);
	void QueryChunksToLoad();
};
