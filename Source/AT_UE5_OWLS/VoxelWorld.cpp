// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelWorld.h"



#include "Engine/World.h"

// Sets default values
AVoxelWorld::AVoxelWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//HashMap = CreateDefaultSubobject<USpatialHashMap>("SpatialHashMap");
	HashMap = CreateDefaultSubobject<USpatialHashMap>("hashmap");
	//GridCells.;
	invCellsize = 1/100/ChunkSize;
}

void AVoxelWorld::AddActor(AActor* Actor)
{
	const FVector& ActorPosition = Actor->GetActorLocation() * invCellsize;
	FIntVector2 hashkey(FMath::FloorToInt(ActorPosition.X), FMath::FloorToInt(ActorPosition.Y));
	if(!GridCells.Contains(hashkey))
	{
		GridCells.Add(hashkey, TArray<AActor*>());
	}
	GridCells[hashkey].Add(Actor);
}

// Called when the game starts or when spawned

void AVoxelWorld::BeginPlay()
{
	Super::BeginPlay();
	for(int x = -DrawDistance; x <= DrawDistance; ++x)
    	{
    		for(int y = -DrawDistance; y <= DrawDistance; ++y)
    		{
    			
    			FIntVector2 hashkey(x,y);
    			AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(Chunk, FVector(x *ChunkSize * 100, y*ChunkSize*100,0), FRotator::ZeroRotator);
    			//GetWorld()->GetSubsystem<>()
    			if(spawnedActor)
    			{
    				
    				//if(!GridCells.Contains(hashkey))
    				//{
    					//GridCells.Add(hashkey, TArray<AActor*>());
    				//}
    				//GridCells[hashkey].Add(spawnedActor);
    				HashMap->AddActor(spawnedActor);
    			}
    				
    		}
    	}

	
	//HashMap->GetActorsInCell(FVector(-3200,-3200,0));
	//HashMap->GetActorsInCell(FVector{-3300,-3300,0});
	
}

// Called every frame
void AVoxelWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

