// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ALevelStreamActor.generated.h"

UCLASS()
class AT_UE5_OWLS_API AALevelStreamActor : public AActor
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	AALevelStreamActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(EditAnywhere)
	FName LevelToLoad;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta= (AllowPrivateAccess = "true"));
	UBoxComponent* _overlapVolume;
private:

};
