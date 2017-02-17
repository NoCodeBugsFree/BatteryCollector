// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Battery(TEXT("StaticMesh'/Game/ExampleContent/Blueprint_Communication/Meshes/SM_Battery_Medium.SM_Battery_Medium'"));
	if (Battery.Succeeded())
	{
		GetMesh()->SetStaticMesh(Battery.Object);
	}

	BatteryPower = 200.f;
}

void ABatteryPickup::WasCollected_Implementation()
{
	// use the base pickup behavior
	Super::WasCollected_Implementation();

	Destroy();
}
