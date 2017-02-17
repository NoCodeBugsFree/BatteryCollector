// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "SpawnVolume.h"
#include "Pickup.h"
#include "BatteryPickup.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	MinSpawnDelay = 1.f;
	MaxSpawnDelay = 5.f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SpawnPickup()
{
	if (WhatToSpawn)
	{
		// SpawnActor
		auto World = GetWorld();
		if(World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
		
			FVector SpawnLocation = GetRandomPointInVolume();
			
			FRotator SpawnRotation = UKismetMathLibrary::RandomRotator();

			APickup* Spawned = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			GetWorldTimerManager().ClearTimer(SpawnTimer);

			SpawnDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);

			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
		}
	} 
	else
	{
		UE_LOG(LogTemp, Error, TEXT("In SpawnVolume Object [WhatToSpawn] propery is nullptr!"));
	}

	
}

