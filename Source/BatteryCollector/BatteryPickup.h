// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()

public:

	ABatteryPickup();

	virtual void WasCollected_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetPower() const { return BatteryPower; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

protected:

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float BatteryPower;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* Emitter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* EmitterTemplate;

	bool bIsStartAttaching = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	ACharacter* Character;	
	
};
