// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryCollector.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup()
{
	PrimaryActorTick.bCanEverTick = true;
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
	//Super::WasCollected_Implementation();
	Emitter = UGameplayStatics::SpawnEmitterAttached(EmitterTemplate, GetMesh());
	SetActorTickEnabled(true);
	SetLifeSpan(2.f);
}

void ABatteryPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Character && Emitter)
	{
		FVector BeamTargetLocation = Character->GetMesh()->GetSocketLocation(FName("spine_02"));
		Emitter->SetBeamTargetPoint(0, BeamTargetLocation, 0);
	}
}

void ABatteryPickup::BeginPlay()
{
	Super::BeginPlay();
	Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	SetActorTickEnabled(false);
}
