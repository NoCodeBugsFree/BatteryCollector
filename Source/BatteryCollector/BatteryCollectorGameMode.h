// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ABatteryCollectorGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditDefaultsOnly, BlueprintReadWrite, Category = "AAA")
	float DecayRate;

private:



};



