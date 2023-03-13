// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpatialHashMap.h"

#include "GameFramework/Actor.h"
#include "VoxelWorld.generated.h"



class USpatialHashMap;
UCLASS()
class AT_UE5_OWLS_API AVoxelWorld : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AVoxelWorld();
	DECLARE_EVENT_OneParam(AVoxelWorld, FObjectHashedEvent, const AActor*);
	FObjectHashedEvent& OnObjectAddedEvent(){return ObjectHashedEvent;}
	UPROPERTY(EditAnywhere, Category="Chunk World")
	TSubclassOf<AActor> Chunk;

	UPROPERTY(EditAnywhere, Category="Chunk World")
	int DrawDistance = 5;

	UPROPERTY(EditAnywhere, Category="Chunk World")
	int ChunkSize = 32;
	float invCellsize;
	void AddActor(AActor* Actor);
	//void RemoveActor(AActor* Actor);
	//TArray<AActor*> GetActorsInCell(const FVector& Position) const;
	TObjectPtr<USpatialHashMap> HashMap;
	TMap<FIntVector2, TArray<AActor*>> GridCells;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BroadcastChanged()
	{

		//AActor* actor;
		
		//ObjectHashedEvent.
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	private:
	FObjectHashedEvent ObjectHashedEvent;
};
