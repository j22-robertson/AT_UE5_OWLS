// Fill out your copyright notice in the Description page of Project Settings.


#include "ALevelStreamActor.h"

#include "SNegativeActionButton.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AALevelStreamActor::AALevelStreamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_overlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Volume"));
	RootComponent = _overlapVolume;

	_overlapVolume->OnComponentBeginOverlap.AddUniqueDynamic(this, &AALevelStreamActor::OverlapBegins);

}

// Called when the game starts or when spawned
void AALevelStreamActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AALevelStreamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
}

void AALevelStreamActor::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));	
	if(LevelToLoad!= "")
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
	}
}

