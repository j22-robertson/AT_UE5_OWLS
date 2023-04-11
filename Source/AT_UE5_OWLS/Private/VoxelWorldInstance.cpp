// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelWorldInstance.h"

UVoxelWorldInstance::UVoxelWorldInstance()
{

	root = new Node;
	root->bounds = 1024;
	root->position = FVector3f{-(16*100*32)/2, -(16*100*32)/2,0};
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

	/*
	for(auto& actor : hashmap.GetActorsInCell(transform))
	{
		//actor->SetActorEnableCollision(true);
	actor->SetHidden(true);
	};*/
	//hashmap.GetActorsInCellByIndex()
	
}

void UVoxelWorldInstance::SpawnWorldTemp()
{
	
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	GameDirectory = FPaths::ProjectDir();
	
	GameDirectory+= WorldName;
	if(FileManager.DirectoryExists(*GameDirectory))
	{
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Directory Exists"));
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Directory Does not exist"));
		FileManager.CreateDirectory(*GameDirectory);
	}
	/*
	for(int x = -DrawScale; x < DrawScale; ++x)
	{
		for(int y = -DrawScale; y < DrawScale; ++y)
		{
    			
			//FIntVector2 hashkey(x,y);
			GetWorld()->SpawnActor<AActor>(Chunk, FVector(x *ChunkSize * 100, y*ChunkSize*100,0), FRotator::ZeroRotator);
		}
	}*/
	//SubdivMaxTest(*root);
}

void UVoxelWorldInstance::QueryAndUnrender( FVector position, float area)
{
	QueryChunksToLoad(*root,position, area);

/*
	const auto& actors = Query(*root, position, area);

	for(const auto& actor: actors)
	{
		actor->SetHidden(true);
	}*/
	
}

void UVoxelWorldInstance::Register(AActor* actor)
{
//	hashmap.AddActor(*actor);
}


void UVoxelWorldInstance::Subdivide(Node& node)
{

	
	//float child_position
	int child_depth = node.depth +1;
	int child_bounds = node.bounds/2;
	float child_offset = (node.bounds*ChunkSize*100)/2;
	//float wtransf = (ChunkSize * 100)/2;
	//float ChildTransf = child_bounds+wtransf;
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
		const FVector3f child_position = node.position;
		
		node.children.Emplace( new Node{FVector3f{child_position.X, child_position.Y,0}
			, child_bounds,
			TArray<AActor*>(), child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X + child_offset,child_position.Y,0}
			, child_bounds,
			TArray<AActor*>(),
			child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X+ child_offset,child_position.Y+child_offset,0},
			child_bounds,
			TArray<AActor*>(),
			child_depth,
		});
		node.children.Emplace( new Node{FVector3f{child_position.X,child_position.Y+child_offset,0}
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
		ChunksToLoad.Enqueue(&node);
		//node.Objects.Add(GetWorld()->SpawnActor<AGreedyChunk>(Chunk, FVector(node.position.X, node.position.Y,0), FRotator::ZeroRotator));
	}
	for(auto child : node.children)
	{
		SubdivMaxTest(*child);
	}
}
bool UVoxelWorldInstance::Intersects(Node& node, FVector position, float area)
{
	
	const float half_area = area/2;
	const float realworldbounds = node.bounds*3200;
	//const float halfrwbounds = realworldbounds/2;
	return (position.X - half_area < node.position.X + realworldbounds&&
		position.X + half_area > node.position.X &&
		position.Y - half_area < node.position.Y + realworldbounds &&
		position.Y +  half_area > node.position.Y);
	
}
void UVoxelWorldInstance::QueryChunksToLoad(Node& node,FVector position, const float& area)
{
	
	if(Intersects(node, position, area))
	{
		if(node.depth != MaxDepth)
		{
			Subdivide(node);
			for(const auto& child : node.children)
			{
				QueryChunksToLoad(*child, position, area);
			}
		}
		else
		{
			ChunksToLoad.Enqueue(&node);
		}
	}
}
void UVoxelWorldInstance::LoadChunk(Node& node) const
{
	if(node.Objects.IsEmpty())
	{
		TArray<AActor* >barnacles = TArray<AActor*>();
		
		node.Objects.Add(GetWorld()->SpawnActor<AGreedyChunk>(Chunk, FVector(node.position.X, node.position.Y,0), FRotator::ZeroRotator));
		barnacles.Add(*node.Objects.begin());
	}
	else
	{
		for(auto& Actor : node.Objects)
		{
			Actor->SetHidden(false);
		}
	}
}
void UVoxelWorldInstance::LoadChunks()
{
	Loaded.Empty();
	ChunksLoaded.Empty();
	while (!ChunksToLoad.IsEmpty())
	{
		auto& node = *ChunksToLoad.Peek();
		LoadChunk(*node);
		Loaded.Add(node);
		ChunksLoaded.Add(node);
		ChunksToLoad.Pop();
	}
}

void UVoxelWorldInstance::LoadParallelChunks()
{
	Loaded.Empty();
	ChunksLoaded.Empty();

	TArray<Node*> ChunksToLoadArray;
	TArray<AActor* >barnacles = TArray<AActor*>();
	while (!ChunksToLoad.IsEmpty())
	{
		auto& node = *ChunksToLoad.Peek();
		
		if(node->Objects.IsEmpty())
		{
			node->Objects.Add(GetWorld()->SpawnActor<AGreedyChunk>(Chunk, FVector(node->position.X, node->position.Y,0), FRotator::ZeroRotator));
			barnacles.Add(*node->Objects.begin());
		}
		else
		{
			for(auto& Actor : node->Objects)
			{
				Actor->SetHidden(false);
			}
		}
		Loaded.Add(node);
		ChunksLoaded.Add(node);
		ChunksToLoadArray.Add(*ChunksToLoad.Peek());

		
		ChunksToLoad.Pop();
	}

	//FParallelForTask::FChunkedTaskResults Results;
	FCriticalSection Mutex;
	ParallelFor(
		barnacles.Num(),
		[&](int32 idx)
		{
			auto& node = *ChunksToLoadArray[idx];
		
		}

	);
}

void UVoxelWorldInstance::UnloadChunks(FVector position, float area)
{
	for (auto& node : PreviousLoaded)
	{
		if(!ChunksLoaded.Contains(node))
		{
			for(auto& actor: node->Objects)
			{
				actor->SetHidden(true);
				actor->Destroy();
				//actor->SetActorEnableCollision(false);
			}
			node->Objects.Empty();
		}
	}
	PreviousLoaded = Loaded;
}

TArray<AActor*> UVoxelWorldInstance::Query(Node& node, FVector position, float area)
{
	TArray<AActor*> result = TArray<AActor*>();
	if(!Intersects(node, position,area*100))
	{
		return result;
	}
	
	if(node.depth != MaxDepth)
	{
		Subdivide(node);
	}
	
	for(auto child : node.children)
	{
		result += Query(*child, position, area*100);
	}
	return result;
}

void UVoxelWorldInstance::SaveLoadWorld()
{
	/*
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString GameDirectory = FPaths::ProjectDir();
	GameDirectory.Append(&WorldName);
	if(FileManager.DirectoryExists(*GameDirectory))
	{
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Directory Exists"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Directory Does not exist"));
		FileManager.CreateDirectory(*GameDirectory);
	}*/
}