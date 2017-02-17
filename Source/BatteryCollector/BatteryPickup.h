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

protected:

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float BatteryPower;

private:
	
	
	
};
