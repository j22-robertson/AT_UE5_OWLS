// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

#include "FastNoiseLite.h"
#include "ProceduralMeshComponent/Public/ProceduralMeshComponent.h"
#include "UObject/ReferenceChainSearch.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
	Noise = new FastNoiseLite();
	
	

	Blocks.SetNum(size*size*size);
	Mesh->SetCastShadow(false);
	
	
	
	
	//fastNoiseWrapper = CreateDefaultSubobject<UFastNoiseWrapper>(TEXT("Noise Generator"));
	

}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
	Noise->SetFrequency(0.03);
	Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise->SetFractalType(FastNoiseLite::FractalType_FBm);
	GenerateBlocks();
	GenerateMesh();
	ApplyMesh();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChunk::GenerateBlocks()
{
	const auto Location = GetActorLocation();

	for (int x = 0; x < size;++x)
	{
		for (int y = 0; y < size;++y)
		{
			const float xpos = (x*100 + Location.X)/100;
			const float y_pos = (y*100+Location.Y)/100;

			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(xpos,y_pos)+1) * size/2),0,size);
			
			
			for (int z = 0; z < Height;++z)
			{
				Blocks[GetBlockIndex(x,y,z)] = EBlockType::Stone;
			}
			for (int z = Height; z < size; ++z)
			{
				Blocks[GetBlockIndex(x,y,z)] = EBlockType::Air;
			}
		}
	}
		
			
}

void AChunk::GenerateMesh()
{
	for (int x = 0; x < size;++x)
	{
		for (int y = 0; y < size;++y)
		{
			for (int z = 0; z < size;++z)
			{
				if(Blocks[GetBlockIndex(x,y,z)] != EBlockType::Air)
				{
					const auto Position = FVector(x,y,z);
					for(auto Direction : {EDirection::Forward, EDirection::Right, EDirection::Back, EDirection::Left, EDirection::Up, EDirection::Down})
					{
						
						if(Check(GetPositionInDirection(Direction, Position)))
						{
							CreateFace(Direction, Position *100);
						}
					}
				}
			}
		}
	}
	
}

void AChunk::ApplyMesh() const
{
	Mesh->CreateMeshSection(0,vertexData,triangleData,TArray<FVector>(),UVData,TArray<FColor>(), TArray<FProcMeshTangent>(),true );
	
}

bool AChunk::Check(FVector Position) const
{
	if(Position.X >= size || Position.Y >= size ||Position.Z >= size || Position.X < 0 || Position.Y <0 ||Position.Z < 0 )
	{
		return true;
	}
	return Blocks[GetBlockIndex(Position.X,Position.Y,Position.Z)] == EBlockType::Air;
}

void AChunk::CreateFace(EDirection Direction, FVector Position)
{
	vertexData.Append(GetFaceVertices(Direction, Position));
	UVData.Append({FVector2D(1,1), FVector2d(1,0), FVector2d(0,0), FVector2d(0,1)});
	triangleData.Append({vertexCount +3, vertexCount + 2, vertexCount, vertexCount + 2, vertexCount + 1, vertexCount});
	vertexCount += 4;
}

TArray<FVector> AChunk::GetFaceVertices(EDirection Direction, FVector Position) const
{
	TArray<FVector> Vertices;

	for(int i = 0; i < 4; ++i)
	{
		Vertices.Add(BlockVertexData[BlockTriangleData[i+static_cast<int>(Direction)*4]]* scale + Position);
;	}
	return Vertices;
}

FVector AChunk::GetPositionInDirection(EDirection Direction, FVector Position)
{
	switch (Direction)
	{
	case EDirection::Forward:  return Position+ FVector::ForwardVector;;
	case EDirection::Right: return Position+ FVector::RightVector;
	case EDirection::Back:return Position+ FVector::BackwardVector; 
	case EDirection::Left: return Position+ FVector::LeftVector;
	case EDirection::Up: return Position+ FVector::UpVector;
	case EDirection::Down: return Position+ FVector::DownVector;
	default: return Position;
	}
}

int AChunk::GetBlockIndex(int x, int y, int z) const
{
	return z * size * size + y * size + x;
}

