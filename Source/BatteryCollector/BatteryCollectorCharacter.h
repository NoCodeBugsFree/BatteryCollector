// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BatteryCollectorCharacter.generated.h"

UCLASS(config=Game)
class ABatteryCollectorCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollectionSphere;

public:
	ABatteryCollectorCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintPure, Category = "AAA")
	float GetInitialPower() const { return InitialPower; }

	UFUNCTION(BlueprintPure, Category = "AAA")
	float GetCurrentPower() const { return CharacterPower; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void UpdatePower(float PowerChange);

	virtual void OnConstruction(const FTransform& Transform) override;


protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void CollectPickups();

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float InitialPower;

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float SpeedFactor;

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float BaseSpeed;

	UPROPERTY(Meta = (BlueprintProtected = "true"), VisibleAnywhere, BlueprintReadWrite, Category = "AAA")
	UMaterialInstanceDynamic* PowerMaterial;

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditAnywhere, BlueprintReadWrite, Category = "AAA")
	FLinearColor StartColor = FLinearColor(0.f, 0.091f, 1.f, 1.f);

	UPROPERTY(Meta = (BlueprintProtected = "true"), EditAnywhere, BlueprintReadWrite, Category = "AAA")
	FLinearColor EndColor = FLinearColor(1.f, 0.31f, 0.f, 1.f);

	UFUNCTION(BlueprintImplementableEvent, Category = "AAA")
	void PowerChangeEffect();

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void PowerChangeEffect_Cpp();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float CharacterPower;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns CollectionSphere subobject **/
	FORCEINLINE class USphereComponent* GetSphereComponent() const { return CollectionSphere; }
};

