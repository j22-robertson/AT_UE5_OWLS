// Fill out your copyright notice in the Description page of Project Settings.


#include "GreedyChunk.h"

#include <string>

#include "FastNoiseLite.h"
#include "VoxelWorldInstance.h"
#include "ProceduralMeshComponent/Public/ProceduralMeshComponent.h"


// Sets default values
AGreedyChunk::AGreedyChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("MyMesh");
	RootComponent = GetRootComponent();
	SetRootComponent(RootComponent);
	//blocks = new TArray<BlockType>();
	MeshData=  new FChunkMeshData();
	
	
	PrimaryActorTick.bCanEverTick = false;
	Blocks = TArray<EBlockType>();
	Blocks.SetNum(size.X * size.Y * size.Z);
	Noise = new FastNoiseLite();
	ToBinary.Empty();
	ToBinary.Seek(0);
	
	

}

// Called when the game starts or when spawned
void AGreedyChunk::BeginPlay()
{
	Super::BeginPlay();
	Noise->SetSeed(12391);
	Noise->SetFrequency(0.03);
	Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise->SetFractalType(FastNoiseLite::FractalType_FBm);
	FIntVector result;
	const int factor =size.X*100;
	const FIntVector iposition = FIntVector(this->GetActorLocation());
	const FIntVector iScaledPosition =FIntVector(this->GetActorLocation()/factor);
	if(iposition.X < 0)
	{
		result.X=iScaledPosition.X-1;
	}
	else
	{
		result.X = iScaledPosition.X;
	}
	if(iposition.Y < 0)
	{
		result.Y=iScaledPosition.Y-1;
	}
	else
	{
		result.Y = iScaledPosition.Y;
	}
	if(iposition.Z < 0)
	{
		result.Z=iScaledPosition.Z-1;
	}
	else
	{
		result.Z = iScaledPosition.Z;
	}


	
	

	filepath  = GetWorld()->GetGameInstance<UVoxelWorldInstance>()->GameDirectory+"/" +this->GetName()+"X" +FString::FromInt(result.X)+"Y"+FString::FromInt(result.Y)+".bin";
	TArray<uint8> BinaryArray;
	

	if (!FFileHelper::LoadFileToArray(BinaryArray, *filepath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load data from file: %s"), *filepath);
		GenerateBlocks();
		GenerateMesh();
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" load data from file: %s"), *filepath);
		FMemoryReader FromBinary = FMemoryReader(BinaryArray, false);
		FromBinary.Seek(0);
		
		check(MeshData)
		{
			FromBinary << *MeshData;
			
			FromBinary << Blocks;
		}
		
		
		
		// true, free data after done
		//FMemoryWriter
		//Tob-
	
		//FBufferArchive myData(BinaryArray);
		//FromBinary.Seek(0);
		//MeshData FromBinary;
		//FromBinary <<MeshData;
		
		FromBinary.FlushCache();
		FromBinary.Close();
	}
	
	if(MeshData)
	{
		ToBinary.Seek(0);
		
		ToBinary << *MeshData;
		ToBinary << Blocks;
	}

	///FString filepath  = TEXT("C:/Users/James Robertson/Documents/Unreal Projects/AT_UE5_OWLS/GameSaveData/SavedData" + this->GetName()+".bin");
	if (FFileHelper::SaveArrayToFile(ToBinary, *filepath))
	{
		
		UE_LOG(LogTemp, Display, TEXT("Data saved to file: %s"), *filepath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save data to file: %s"), *filepath);
	}
	ToBinary.FlushCache();
	ToBinary.Empty();
	
	ApplyMesh();

	//const auto& temp = Cast<UVoxelWorldInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//temp->Register(this);

	// Deserialize the binary data into a FMemoryReader instance
	//FMemoryReader MemoryReader(BinaryArray, true); // true to free the buffer after done
	//MemoryReader.Seek(0);

	

	//ToBinary << Blocks;
	
	//FArchive archive;
	//archive << this->MeshData;
	//archive << this->blocks;
	//archive << this->scale;
	//archive << this->size;
}

void AGreedyChunk::EditChunk(const FIntVector& position, const EBlockType& block)
{
	if(position.X > size.X || position.X <0||position.Y > size.Y || position.Y <0||position.Z > size.Z || position.Z <0)
	{
		return;
	}
	EditChunkMesh(position, block);
	ClearMesh();
	GenerateMesh();
	ApplyMesh();

	FBufferArchive NewToBinary;
	NewToBinary << *MeshData;
	NewToBinary << Blocks;
	
	
	if ( FFileHelper::SaveArrayToFile(NewToBinary, *filepath))
	{
		
		UE_LOG(LogTemp, Display, TEXT("Data saved to file: %s"), *filepath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save data to file: %s"), *filepath);
	}
	ToBinary.FlushCache();
	// Empty the buffer archive to free memory
	ToBinary.Empty();
}
void AGreedyChunk::ClearMesh()
{
	vertcount = 0;
	MeshData->Clear();
}

void AGreedyChunk::EditChunkMesh(const FIntVector& position, const EBlockType& block)
{
	const int index = GetBlockIndex(position.X,position.Y,position.Z);
	Blocks[index] = block;
	
}

// Called every frame
void AGreedyChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGreedyChunk::GenerateBlocks()
{
	const auto& Location = GetActorLocation();

	for (int x = 0; x < size.X; x++)
	{
		for (int y = 0; y < size.Y; y++)
		{
			const float Xpos = (x * 100 + Location.X) / 100;
			const float ypos = (y * 100 + Location.Y) / 100;

			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(Xpos, ypos) + 1) * size.Z / 2), 0, size.Z);

			for (int z = 0; z < Height; z++)
			{
				Blocks[GetBlockIndex(x,y,z)] = EBlockType::Stone;
			}

			for (int z = Height; z < size.Z; z++)
			{
				Blocks[GetBlockIndex(x,y,z)] = EBlockType::Air;
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

					const bool CurrentBlockOpaque = CurrentBlock != EBlockType::Air;
					const bool CompareBlockOpaque = CompareBlock != EBlockType::Air;

					if (CurrentBlockOpaque == CompareBlockOpaque)
					{
						Mask[N++] = FMask { EBlockType::Null, 0 };
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
								Mask[N + k + l * Axis1Limit] = FMask { EBlockType::Null, 0 };
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

EBlockType AGreedyChunk::GetBlock(const FIntVector Index) const
{
	if (Index.X >= size.X || Index.Y >= size.Y || Index.Z >= size.Z || Index.X < 0 || Index.Y < 0 || Index.Z < 0)
		return EBlockType::Air;
	return Blocks[GetBlockIndex(Index.X, Index.Y, Index.Z)];
}

bool AGreedyChunk::CompareMask(const FMask M1, const FMask M2) const
{
	return M1.Block == M2.Block && M1.Normal == M2.Normal;
}