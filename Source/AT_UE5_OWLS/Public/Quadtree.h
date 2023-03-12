// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
 struct Node
 {
 	FVector3f position;
	FVector2D bounds;
 	TArray<TObjectPtr<UObject>> Objects;
 	TObjectPtr<Node> children[4];
 };
 
class AT_UE5_OWLS_API Quadtree
{
public:
	Quadtree(FVector3f position, FVector2d bounds, int maxObjectsPerNode);
	void Insert(UObject* Object);
	TArray<TObjectPtr<UObject>> Query(FVector2d bounds);
private:

	TObjectPtr<Node> root;
	int maxObjectsPerNode;
	void Subdivide(TObjectPtr<Node> node);
	TArray<UObject*> Query(TObjectPtr<Node> node, FVector2d bounds);
	
	~Quadtree();
};
