// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharMovementComponent.h"
#include <TicTacToe/PlayerChar.h>

UPlayerCharMovementComponent::UPlayerCharMovementComponent()
{
	UE_LOG(LogTemp, Log, TEXT("[Load] Player Char Movement Component"));
}

void UPlayerCharMovementComponent::TickComponent(
	float DeltaTime, 
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	SneakLoop();
	WalkLoop(DeltaTime);
}

bool UPlayerCharMovementComponent::WalkLoop(float DeltaTime)
{
	APlayerChar* p = Cast<APlayerChar>(PawnOwner);
	if (p == nullptr) {
		return false;
	}
	FVector forward_direction = p->GetActorForwardVector();
	FVector right_direction = p->GetActorRightVector();
	//AddInputVector(forward_velocity * walkAxisValue * FMath::Square(currentWalkSpeed));
	p->AddMovementInput(forward_direction * DeltaTime * 100, walkForwardAxisValue, false);
	p->AddMovementInput(right_direction * DeltaTime * 100, walkRightAxisValue, false);
	return true;
}

void UPlayerCharMovementComponent::SneakLoop()
{
	if (bPressedSneak && canNowSneak) {
		isSneaking = true;
		PawnOwner->BaseEyeHeight = 32;
		APlayerChar* p = Cast<APlayerChar>(PawnOwner);
	}
	else if (isSneaking && !bPressedSneak) {
		isSneaking = false;
		PawnOwner->BaseEyeHeight = 64;

		if (wasRunning) {
			APlayerChar* p = Cast<APlayerChar>(PawnOwner);
			if (p != nullptr) {
				p->timerrun = false;
				p->time = 0.0f;
				p->ResetCamera();
			}
			wasRunning = false;
		}
	}

}
