// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_BatteryCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	DecayRate = 0.01f;
	
}

void ABatteryCollectorGameMode::BeginPlay()
{
	Super::BeginPlay();

	ABatteryCollectorCharacter* BatteryCollectorCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (BatteryCollectorCharacter)
	{
		PowerToWin = BatteryCollectorCharacter->GetInitialPower() * 1.25f;
		Character = BatteryCollectorCharacter;
	}

	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

float ABatteryCollectorGameMode::GetHudPercent() const
{
	if (Character)
	{
		return Character->GetCurrentPower() / PowerToWin;
	} 
	else
	{
		return 0.f;
	}
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ABatteryCollectorCharacter* BatteryCollectorCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (BatteryCollectorCharacter)
	{
		if (BatteryCollectorCharacter->GetCurrentPower() > 0)
		{
			BatteryCollectorCharacter->UpdatePower(-DeltaTime * DecayRate * (BatteryCollectorCharacter->GetInitialPower()));
			if (ProgressBarReference)
			{
				ProgressBarReference->SetPercent(BatteryCollectorCharacter->GetCurrentPower() / PowerToWin);
			}
		}
	}
}


