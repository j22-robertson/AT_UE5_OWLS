// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelWorld.h"

#include "Engine/World.h"

// Sets default values
AVoxelWorld::AVoxelWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoxelWorld::BeginPlay()
{
	Super::BeginPlay();

	for(int x = -DrawDistance; x <= DrawDistance; ++x)
	{
		for(int y = -DrawDistance; y <= DrawDistance; ++y)
		{
			
			GetWorld()->SpawnActor<AActor>(Chunk, FVector(x *ChunkSize * 100, y*ChunkSize*100,0), FRotator::ZeroRotator);
		}
	}
	
}

// Called every frame
void AVoxelWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

