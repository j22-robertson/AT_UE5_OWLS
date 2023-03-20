// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelWorldInstance.h"

UVoxelWorldInstance::UVoxelWorldInstance()
{

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
	
	//hashmap.GetActorsInCellByIndex()
	
}
void UVoxelWorldInstance::Register(AActor* actor)
{
	hashmap.AddActor(*actor);
}
