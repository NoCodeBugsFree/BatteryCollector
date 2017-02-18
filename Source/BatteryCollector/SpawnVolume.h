// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	UFUNCTION(BlueprintPure, Category = "AAA")
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SpawnPickup();

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetSpawningActive(bool bShouldSpawn);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", Meta = (BlueprintProtected = "true"))
	float MinSpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", Meta = (BlueprintProtected = "true"))
	float MaxSpawnDelay;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* WhereToSpawn;

	float SpawnDelay;
	
};
