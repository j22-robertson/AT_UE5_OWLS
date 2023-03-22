// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelWorldInstance.h"

UVoxelWorldInstance::UVoxelWorldInstance()
{

	root = new Node;
	root->bounds = 32;
	root->position = FVector3f(0,0,0);
	root->depth = 0;
	int i = 0;
	int minchildbounds = root->bounds;
	while(minchildbounds != 1)
	{
		minchildbounds/= 2;
		i++;
	}
	MaxDepth = i;
	ChunkSize = 32;

	//SubdivMaxTest(*root);
	// = i;
	///this->maxObjectsPerNode = _maxObjectsPerNode;
	//VoxelWorldTree = FQuadtree{FVector3f{0,0,0}, 1028, 50, 32 };
	//Quadtree = new FQuadtree(FVector3f{0,0,0}, 1028, 50, 32 );

	//Quadtree->TempSubdivFromGameInstance();
}

void UVoxelWorldInstance::PrintStuff(int num)
{
	
	UE_LOG(LogTemp, Log, TEXT("HEEEEEEEEEEEEEERE"));
}

void UVoxelWorldInstance::LoadData()
{
	//FText outerr;
	//FFileHelper::IsFilenameValidForSaving("b",outerr );
	
}

void UVoxelWorldInstance::UpdateChunksLoaded(const FVector3f& transform)
{
	for(auto& actor : hashmap.GetActorsInCell(transform))
	{
		//actor->SetActorEnableCollision(true);
	actor->SetHidden(true);
	};
	//hashmap.GetActorsInCellByIndex()
	
}

void UVoxelWorldInstance::SpawnWorldTemp()
{
	/*
	for(int x = -DrawScale; x < DrawScale; ++x)
	{
		for(int y = -DrawScale; y < DrawScale; ++y)
		{
    			
			//FIntVector2 hashkey(x,y);
			GetWorld()->SpawnActor<AActor>(Chunk, FVector(x *ChunkSize * 100, y*ChunkSize*100,0), FRotator::ZeroRotator);
		}
	}*/
	SubdivMaxTest(*root);
}

void UVoxelWorldInstance::Register(AActor* actor)
{
	hashmap.AddActor(*actor);
}


void UVoxelWorldInstance::Subdivide(Node& node)
{
	
	int child_depth = node.depth +1;
	int child_bounds = node.bounds/2;
	float wtransf = (ChunkSize * 100)/2;
	/*
	while(child_bounds%32 != 0)
	{
		child_bounds+=1;
		if(child_bounds ==32)
		{
			
		}
	}*/

	// -1,+1,
	//+1,+1,
	//+1,-1
	//-1,-1
	if(node.children.IsEmpty())
	{
		FVector3f child_position = node.position;
		node.children.Emplace( new Node{FVector3f{child_position.X-child_bounds* wtransf,child_position.Y+child_bounds*wtransf,child_position.Z}
			, child_bounds,
			TArray<AActor*>(), child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X+child_bounds* wtransf,child_position.Y+child_bounds* wtransf,child_position.Z}
			, child_bounds,
			TArray<AActor*>(),
			child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X+child_bounds* wtransf,child_position.Y-child_bounds* wtransf,child_position.Z},
			child_bounds,
			TArray<AActor*>(),
			child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X-child_bounds*wtransf,child_position.Y-child_bounds* wtransf,child_position.Z}
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
					/*
					if(Contains(actor->GetActorLocation(), node))
					{
						Insert(*child,actor);
					}*/
				}
			}
		}
		//node.Objects.Empty();
	}
}

void UVoxelWorldInstance::SubdivMaxTest(Node& node)
{
	if(node.depth != MaxDepth)
	{
		Subdivide(node);
	}
	else
	{
		GetWorld()->SpawnActor<AGreedyChunk>(Chunk, FVector(node.position.X, node.position.Y,0), FRotator::ZeroRotator);
	}
	for(auto child : node.children)
	{
		SubdivMaxTest(*child);
	}
}
bool UVoxelWorldInstance::Intersects(Node& node, FVector position, float area)
{

	return (position.X < node.position.X + node.bounds &&
		position.X + area > node.position.X &&
		position.Y < node.position.Y + node.bounds &&
		position.Y + area > node.position.Y);
	
}
