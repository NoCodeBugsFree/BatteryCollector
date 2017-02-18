// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollector.h"
#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"
#include "SpawnVolume.h"

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

	ItitializeSpawnVolumes();

	SetCurrentPlayState(EBatteryPlayState::EPlaying);

	ABatteryCollectorCharacter* BatteryCollectorCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (BatteryCollectorCharacter)
	{
		PowerToWin = BatteryCollectorCharacter->GetInitialPower() * 1.25f;
		Character = BatteryCollectorCharacter;
	}

	CreateHUD();
}

void ABatteryCollectorGameMode::CreateHUD()
{
	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ABatteryCollectorGameMode::ItitializeSpawnVolumes()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(Actor);
		if (SpawnVolume)
		{
			SpawnVolumes.AddUnique(SpawnVolume);
		}
	}
}

void ABatteryCollectorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ABatteryCollectorCharacter* BatteryCollectorCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (BatteryCollectorCharacter)
	{
		// WIN
		if (BatteryCollectorCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentPlayState(EBatteryPlayState::EWon);
			ProgressBarReference->SetPercent(1.f);
		}
		else if (BatteryCollectorCharacter->GetCurrentPower() > 0)
		{
			BatteryCollectorCharacter->UpdatePower(-DeltaTime * DecayRate * (BatteryCollectorCharacter->GetInitialPower()));
			if (ProgressBarReference)
			{
				ProgressBarReference->SetPercent(BatteryCollectorCharacter->GetCurrentPower() / PowerToWin);
			}
		}
		else // LOSE
		{
			SetCurrentPlayState(EBatteryPlayState::EGameOver);
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

void ABatteryCollectorGameMode::SetCurrentPlayState(EBatteryPlayState NewPlayState)
{
	CurrentPlayState = NewPlayState;
	HandleNewState(CurrentPlayState);
}

void ABatteryCollectorGameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
		case EBatteryPlayState::EPlaying:
		{
			for (ASpawnVolume* SpawnVolume : SpawnVolumes)
			{
				SpawnVolume->SetSpawningActive(true);
			}
		}
		break;

		case EBatteryPlayState::EWon:
		{
			for (ASpawnVolume* SpawnVolume : SpawnVolumes)
			{
				SpawnVolume->SetSpawningActive(false);
			}
		}
		break;

		case EBatteryPlayState::EGameOver:
		{
			for (ASpawnVolume* SpawnVolume : SpawnVolumes)
			{
				SpawnVolume->SetSpawningActive(false);
			}

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (PlayerController)
			{
				PlayerController->SetCinematicMode(true, false, false, true, true);
			}

			ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (Character)
			{
				Character->GetMesh()->SetSimulatePhysics(true);
				Character->GetMovementComponent()->MovementState.bCanJump = false;
			}
		}
		break;

		default:
		case EBatteryPlayState::EUnknown:
		{
			// do nothing
		}
		break;
	}
}
