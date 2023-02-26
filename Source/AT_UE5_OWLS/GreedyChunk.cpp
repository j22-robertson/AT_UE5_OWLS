// Fill out your copyright notice in the Description page of Project Settings.


#include "GreedyChunk.h"
#include "FastNoiseLite.h"
#include "ProceduralMeshComponent/Public/ProceduralMeshComponent.h"

// Sets default values
AGreedyChunk::AGreedyChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("MyMesh");
	
	MeshData = new FChunkMeshData();
	PrimaryActorTick.bCanEverTick = false;
	Blocks.SetNum(size.X * size.Y * size.Z);
	Noise = new FastNoiseLite();

}

// Called when the game starts or when spawned
void AGreedyChunk::BeginPlay()
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
void AGreedyChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreedyChunk::GenerateBlocks()
{
	const auto Location = GetActorLocation();

	for (int x = 0; x < size.X; x++)
	{
		for (int y = 0; y < size.Y; y++)
		{
			const float Xpos = (x * 100 + Location.X) / 100;
			const float ypos = (y * 100 + Location.Y) / 100;

			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(Xpos, ypos) + 1) * size.Z / 2), 0, size.Z);

			for (int z = 0; z < Height; z++)
			{
				Blocks[GetBlockIndex(x,y,z)] = BlockType::Stone;
			}

			for (int z = Height; z < size.Z; z++)
			{
				Blocks[GetBlockIndex(x,y,z)] = BlockType::Air;
			}

		}
	}
}

void AGreedyChunk::GenerateMesh()
{
	for (int Axis = 0; Axis < 3; ++Axis)
	{
		// 2 Perpendicular axis
		const int Axis1 = (Axis + 1) % 3;
		const int Axis2 = (Axis + 2) % 3;

		const int MainAxisLimit = size[Axis];
		int Axis1Limit = size[Axis1];
		int Axis2Limit = size[Axis2];

		auto DeltaAxis1 = FIntVector::ZeroValue;
		auto DeltaAxis2 = FIntVector::ZeroValue;

		auto ChunkItr = FIntVector::ZeroValue;
		auto AxisMask = FIntVector::ZeroValue;

		AxisMask[Axis] = 1;

		TArray<FMask> Mask;
		Mask.SetNum(Axis1Limit * Axis2Limit);

		// Check each slice of the chunk
		for (ChunkItr[Axis] = -1; ChunkItr[Axis] < MainAxisLimit;)
		{
			int N = 0;

			// Compute Mask
			for (ChunkItr[Axis2] = 0; ChunkItr[Axis2] < Axis2Limit; ++ChunkItr[Axis2])
			{
				for (ChunkItr[Axis1] = 0; ChunkItr[Axis1] < Axis1Limit; ++ChunkItr[Axis1])
				{
					const auto CurrentBlock = GetBlock(ChunkItr);
					const auto CompareBlock = GetBlock(ChunkItr + AxisMask);

					const bool CurrentBlockOpaque = CurrentBlock != BlockType::Air;
					const bool CompareBlockOpaque = CompareBlock != BlockType::Air;

					if (CurrentBlockOpaque == CompareBlockOpaque)
					{
						Mask[N++] = FMask { BlockType::Null, 0 };
					}
					else if (CurrentBlockOpaque)
					{
						Mask[N++] = FMask { CurrentBlock, 1 };
					}
					else
					{
						Mask[N++] = FMask { CompareBlock, -1 };
					}
				}
			}

			++ChunkItr[Axis];
			N = 0;

			// Generate Mesh From Mask
			for (int j = 0; j < Axis2Limit; ++j)
			{
				for (int i = 0; i < Axis1Limit;)
				{
					if (Mask[N].Normal != 0)
					{
						const auto CurrentMask = Mask[N];
						ChunkItr[Axis1] = i;
						ChunkItr[Axis2] = j;

						int Width;

						for (Width = 1; i + Width < Axis1Limit && CompareMask(Mask[N + Width], CurrentMask); ++Width)
						{

						}

						int Height;
						bool Done = false;

						for (Height = 1; j + Height < Axis2Limit; ++Height)
						{
							for (int k = 0; k < Width; ++k)
							{
								if (CompareMask(Mask[N + k + Height * Axis1Limit], CurrentMask)) continue;

								Done = true;
								break;
							}

							if (Done) break;
						}

						DeltaAxis1[Axis1] = Width;
						DeltaAxis2[Axis2] = Height;

						CreateQuad(
							CurrentMask, AxisMask,
							ChunkItr,
							ChunkItr + DeltaAxis1,
							ChunkItr + DeltaAxis2,
							ChunkItr + DeltaAxis1 + DeltaAxis2
						);

						DeltaAxis1 = FIntVector::ZeroValue;
						DeltaAxis2 = FIntVector::ZeroValue;

						for (int l = 0; l < Height; ++l)
						{
							for (int k = 0; k < Width; ++k)
							{
								Mask[N + k + l * Axis1Limit] = FMask { BlockType::Null, 0 };
							}
						}

						i += Width;
						N += Width;
					}
					else
					{
						i++;
						N++;
					}
				}
			}
		}
	}
}

void AGreedyChunk::ApplyMesh() const
{
	Mesh->CreateMeshSection(0, MeshData->Vertices, MeshData->Triangles, MeshData->Normals, MeshData->UV0, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}
void AGreedyChunk::CreateQuad(FMask Mask, FIntVector AxisMask, FIntVector V1, FIntVector V2, FIntVector V3, FIntVector V4)
{
	const auto Normal = FVector(AxisMask * Mask.Normal);

	MeshData->Vertices.Add(FVector(V1) * 100);
	MeshData->Vertices.Add(FVector(V2) * 100);
	MeshData->Vertices.Add(FVector(V3) * 100);
	MeshData->Vertices.Add(FVector(V4) * 100);

	MeshData->Triangles.Add(vertcount);
	MeshData->Triangles.Add(vertcount + 2 + Mask.Normal);
	MeshData->Triangles.Add(vertcount + 2 - Mask.Normal);
	MeshData->Triangles.Add(vertcount + 3);
	MeshData->Triangles.Add(vertcount + 1 - Mask.Normal);
	MeshData->Triangles.Add(vertcount + 1 + Mask.Normal);

	MeshData->UV0.Add(FVector2D(0,0));
	MeshData->UV0.Add(FVector2D(0,1));
	MeshData->UV0.Add(FVector2D(1,0));
	MeshData->UV0.Add(FVector2D(1,1));

	MeshData->Normals.Add(Normal);
	MeshData->Normals.Add(Normal);
	MeshData->Normals.Add(Normal);
	MeshData->Normals.Add(Normal);
	vertcount += 4;
}

int AGreedyChunk::GetBlockIndex(const int X, const int Y, const int Z) const
{	
	return Z * size.X * size.Y + Y * size.X + X;
}

BlockType AGreedyChunk::GetBlock(const FIntVector Index) const
{
	if (Index.X >= size.X || Index.Y >= size.Y || Index.Z >= size.Z || Index.X < 0 || Index.Y < 0 || Index.Z < 0)
		return BlockType::Air;
	return Blocks[GetBlockIndex(Index.X, Index.Y, Index.Z)];
}

bool AGreedyChunk::CompareMask(const FMask M1, const FMask M2) const
{
	return M1.Block == M2.Block && M1.Normal == M2.Normal;
}