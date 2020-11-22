// Fill out your copyright notice in the Description page of Project Settings.


#include "Horn.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AHorn::AHorn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(Root);

}

void AHorn::PrimaryFire() 
{
	FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	UGameplayStatics::SpawnEmitterAtLocation(this,HornLaser,SpawnLocation, SpawnRotation);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn != nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController != nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
}

// Called when the game starts or when spawned
void AHorn::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void AHorn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

