// Fill out your copyright notice in the Description page of Project Settings.


#include "Quadtree.h"



FQuadtree::FQuadtree(FVector3f _position, int _bounds, int _maxObjectsPerNode, int _ChunkSize): ChunkSize(_ChunkSize)
{
	root = new Node;
	root->bounds = _bounds;
	root->position = _position;
	root->depth = 0;
	int i = 0;
	int minchildbounds = _bounds;
	while(minchildbounds != ChunkSize)
	{
		minchildbounds/= 2;
		i++;
	}
	MaxDepth = i;
	this->maxObjectsPerNode = _maxObjectsPerNode;

	
}

void FQuadtree::Subdivide(Node& node)
{
	
	int child_depth = node.depth +1;
	int child_bounds = node.bounds/2;
	while(child_bounds%ChunkSize != 0)
	{
		child_bounds+=1;
		if(child_bounds == ChunkSize)
		{
			
		}
	}

	// -1,+1,
	//+1,+1,
	//+1,-1
	//-1,-1
	if(node.children.IsEmpty())
	{
		FVector3f child_position = node.position;
		node.children.Emplace( new Node{FVector3f{child_position.X-child_bounds,child_position.Y+child_bounds,child_position.Z}
			, child_bounds,
			TArray<AActor*>(), child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X+child_bounds,child_position.Y+child_bounds,child_position.Z}
			, child_bounds,
			TArray<AActor*>(),
			child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X+child_bounds,child_position.Y-child_bounds,child_position.Z},
			child_bounds,
			TArray<AActor*>(),
			child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X-child_bounds,child_position.Y-child_bounds,child_position.Z}
			, child_bounds,
			TArray<AActor*>(),
			child_depth,
		});

		for(auto& child : node.children)
		{
			check(child)
			{
				for(auto actor : node.Objects)
				{
					if(Contains(actor->GetActorLocation(), node))
					{
						Insert(*child,actor);
					}
				}
			}
		}
		//node.Objects.Empty();
	
	}
	
}

void FQuadtree::LoadChunks(FVector actorposition, Node& node)
{

	//change to intersects?
	if(Contains(actorposition, node) && node.depth != MaxDepth)
	{
		if(node.depth != MaxDepth)
		{
			Subdivide(node);
		}
		for(auto child : node.children)
		{
         		LoadChunks(actorposition, *child);
		}
	}
	
	
}

bool FQuadtree::Contains(FVector actorposition, Node& node)
{
	
	   return (actorposition.X >= node.position.X && actorposition.X <= node.position.X + node.bounds &&
			   actorposition.Y >= node.position.Y && actorposition.Y <= node.position.Y + node.bounds);
}

void FQuadtree::Insert(Node& node, AActor* actor)
{
	node.Objects.Add(actor);
}
bool FQuadtree::Intersects(Node& node, FVector position, float area)
{

	return (position.X < node.position.X + node.bounds &&
		position.X + area > node.position.X &&
		position.Y < node.position.Y + node.bounds &&
		position.Y + area > node.position.Y);
	
}

TArray<AActor*> FQuadtree::Query(Node& node, FVector position, float area)
{
	TArray<AActor*> result = TArray<AActor*>();
	if(!Intersects(node, position,area))
	{
		return result;
	}
	
	if(node.children.IsEmpty())
	{
		return result;
	}
	
	for(auto child : node.children)
	{
		result += Query(*child, position, area);
	}
	return result;

	
	
	
}

void FQuadtree::TempSubdivFromGameInstance()
{
	Subdivide(*root);
}

FQuadtree::~FQuadtree()
{
}
