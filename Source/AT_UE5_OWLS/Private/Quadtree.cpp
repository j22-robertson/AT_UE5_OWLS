// Fill out your copyright notice in the Description page of Project Settings.


#include "Quadtree.h"


Quadtree::Quadtree(FVector3f position, FVector2d bounds, int maxObjectsPerNode)
{
	root = new Node;
	root->bounds = bounds;
	root->position = position;
	this->maxObjectsPerNode = maxObjectsPerNode;
}

Quadtree::~Quadtree()
{
}
