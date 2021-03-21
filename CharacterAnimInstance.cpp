// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitalizeAnimation() 
{
    if (Pawn == nullptr)
    {
        Pawn = TryGetPawnOwner();
    }
}

void UCharacterAnimInstance::UpdateAnimationProperties() 
{
    if (Pawn == nullptr)
    {
        Pawn = TryGetPawnOwner();
    }

    if (Pawn)
    {
        FVector Speed = Pawn->GetVelocity();
        FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
        MovementSpeed = LateralSpeed.Size();
        
        bIsInAir = Pawn->GetMovementComponent()->IsFalling();
        
        FTransform ActorTransform = Pawn->GetActorTransform();
        UE_LOG(LogTemp, Warning, TEXT("Transform = : %s"), *ActorTransform.ToString());

    }
}