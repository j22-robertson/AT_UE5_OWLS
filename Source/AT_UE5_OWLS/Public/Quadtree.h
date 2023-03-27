// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */
 struct Node
 {
 	FVector3f position;
	int bounds;
 	
 	TArray<AActor*> Objects;
 	int depth;
 	TArray<Node*> children;
 };


struct AT_UE5_OWLS_API FQuadtree
{
	
public:
	void Subdivide(Node& node);
	FQuadtree(FVector3f _position, int _bounds, int _maxObjectsPerNode, int _ChunkSize);
	//void Insert(UObject* Object);
	//TArray<AActor*> Query(TObjectPtr<Node> node, FVector2d bounds);
	~FQuadtree();void TempSubdivFromGameInstance();
private:
	const int ChunkSize;
	Node* root;
	int maxObjectsPerNode;
	
	void LoadChunks(FVector actorposition, Node& node);
	bool Contains(FVector actorposition, Node& node);
	void Insert(Node& node, AActor* actor);
	bool Intersects(Node& node, FVector position, float area);
	TArray<AActor*> Query(Node& node, FVector position, float area);
	
	int MaxDepth;


	
};
