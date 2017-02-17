// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
	RootComponent = PickupMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Battery(TEXT("StaticMesh'/Game/ExampleContent/Blueprint_Communication/Meshes/SM_Battery_Medium.SM_Battery_Medium'"));
	if(Battery.Succeeded())
	{
		PickupMesh->SetStaticMesh(Battery.Object);
	}
	
	bIsActive = true;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

