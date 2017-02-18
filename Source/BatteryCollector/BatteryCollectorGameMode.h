// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ABatteryCollectorGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void CreateHUD();

	UFUNCTION()
	void ItitializeSpawnVolumes();

	UFUNCTION(BlueprintPure, Category = "AAA")
	float GetPowerToWin() const { return PowerToWin; }

	UFUNCTION(BlueprintPure, Category = "AAA")
	float GetHudPercent() const;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetProgressBarReference(UProgressBar* ProgressBarReferenceToSet) { ProgressBarReference = ProgressBarReferenceToSet; }

	UFUNCTION(BlueprintPure, Category = "AAA")
	EBatteryPlayState GetCurrentPlayState() const { return CurrentPlayState; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetCurrentPlayState(EBatteryPlayState NewPlayState);

protected:

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditDefaultsOnly, BlueprintReadWrite, Category = "AAA")
	float DecayRate;

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditDefaultsOnly, BlueprintReadWrite, Category = "AAA")
	float PowerToWin;

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditDefaultsOnly, BlueprintReadWrite, Category = "AAA")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	UPROPERTY()
	class ABatteryCollectorCharacter* Character;

	UPROPERTY()
	class UProgressBar* ProgressBarReference;

private:

	UFUNCTION()
	void HandleNewState(EBatteryPlayState NewState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<class ASpawnVolume*> SpawnVolumes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EBatteryPlayState CurrentPlayState = EBatteryPlayState::EPlaying;

};



