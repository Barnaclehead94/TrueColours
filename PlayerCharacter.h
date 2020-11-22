// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

class AHorn;

UCLASS()
class TRUECOLOURS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHorn> HornClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))	
	USpringArmComponent* SAC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))	
	UCameraComponent* Cam;

	UPROPERTY()
	AHorn* Horn;

	// COMPONENTS
	float DefaultArmLength = 600.f;
	float CombatArmLength = 950.f;

	FRotator DefaultSpringArmRot = FRotator(-10.f, 0.f, 0.f);

	FRotator CombatSpringArmRot = FRotator(-20.5f, 0.f, 0.f);
	
	// MOVEMENT
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	//COMBAT
	void PrimaryFire();
	UPROPERTY()
	bool CombatMode;
	void Draw();

	bool FirstPerson;
};
