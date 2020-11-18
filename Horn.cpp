// Fill out your copyright notice in the Description page of Project Settings.


#include "Horn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

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

	UGameplayStatics::SpawnEmitterAttached(HornLaser, ProjectileSpawnPoint, NAME_None, SpawnLocation, SpawnRotation);
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

