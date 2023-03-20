// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpatialHashMap.h"
#include "Engine/GameInstance.h"
#include "VoxelWorldInstance.generated.h"

/**
 * 
 */
UCLASS()
class AT_UE5_OWLS_API UVoxelWorldInstance : public UGameInstance
{
	GENERATED_BODY()
	UVoxelWorldInstance();
	FSpatialHashMap hashmap;


	UFUNCTION(BlueprintCallable)
	void PrintStuff(int num);
	UFUNCTION(BlueprintCallable)
	void UpdateChunksLoaded(const FVector3f& transform);
public:
	void LoadData();
	
	
	void Register(AActor* actor);
};
