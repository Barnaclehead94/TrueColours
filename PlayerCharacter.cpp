// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Horn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraC"));

	SAC = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmC"));
	SAC->SetupAttachment(RootComponent);
	SAC->TargetArmLength = DefaultArmLength;
	SAC->SetRelativeRotation(DefaultSpringArmRot);
	

	Cam->AttachTo(SAC, USpringArmComponent::SocketName);

	CombatMode = false;

	SAC->bEnableCameraRotationLag = true;
	SAC->CameraRotationLagSpeed = 4;
	SAC->CameraLagMaxTimeStep = 1;
	
	SAC->bEnableCameraLag = true;
	SAC->CameraLagSpeed = 20;
	SAC->CameraLagMaxDistance = 20;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	Horn = GetWorld()->SpawnActor<AHorn>(HornClass);
	if (HornClass)
	{
	Horn->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HornSocket"));
	Horn->SetOwner(this);
	}

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("PrimaryFire"), EInputEvent::IE_Pressed, this, &APlayerCharacter::PrimaryFire);
	PlayerInputComponent->BindAction(TEXT("Draw"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Draw);
}

void APlayerCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);	

	// if (CombatMode)
	// {
	// 	Cam->AddLocalRotation(FRotator(AxisValue,0,0));
	// }
	// else
	// {
	// 	SAC->AddLocalRotation(FRotator(AxisValue,0,0));
	// }

	// if (AxisValue)
	// {
	// 	float temp = SAC->GetRelativeRotation().Pitch + AxisValue;
	// 	if (temp < 25 && temp > -65)
	// 	{
	// 		SAC->AddLocalRotation(FRotator(AxisValue, 0, 0));
	// 	}
	// }
}

void APlayerCharacter::LookUpRate(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Draw() 
{

	FVector DefaultSACSocketOffset = FVector(0.f, 0.f, 0.f);
	FVector CombatSACSocketOffset = FVector(0.f,0.f,70.f);

	if (CombatMode)
	{
		SAC->bEnableCameraRotationLag = true;
		SAC->CameraRotationLagSpeed = 4;
		SAC->CameraLagMaxTimeStep = 1;
		
		SAC->bEnableCameraLag = true;
		SAC->CameraLagSpeed = 20;
		SAC->CameraLagMaxDistance = 20;

		SAC->TargetArmLength = DefaultArmLength;
		SAC->TargetOffset = DefaultSACSocketOffset;
		SAC->SetRelativeRotation(DefaultSpringArmRot);
		UE_LOG(LogTemp, Warning, TEXT("Weapon holstered"));
		CombatMode = false;
	}
	else
	{
		SAC->bEnableCameraRotationLag = false;
		SAC->bEnableCameraLag = false;

		SAC->TargetArmLength = CombatArmLength;
		SAC->TargetOffset = CombatSACSocketOffset;
		SAC->SetRelativeRotation(CombatSpringArmRot);
		SAC->SetRelativeLocation(FVector(90.0f, 0.f, 100.f));
		UE_LOG(LogTemp, Warning, TEXT("Weapon drawn"));
		CombatMode = true;
	}
}

void APlayerCharacter::PrimaryFire() 
{
	if (CombatMode)
	{
		Horn->PrimaryFire();
	}
}


