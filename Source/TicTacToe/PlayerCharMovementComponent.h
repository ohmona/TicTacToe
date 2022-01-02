// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API UPlayerCharMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UPlayerCharMovementComponent();

protected:
	virtual void TickComponent(
		float DeltaTime, 
		enum ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction
	) override;

public:
	void SneakLoop();
	bool WalkLoop(float DeltaTime);

public:
	bool bPressedSneak = false;
	bool canNowSneak = true;
	bool isSneaking = false;
	bool wasRunning = false;

	float walkForwardAxisValue = 0.0f;
	float walkRightAxisValue = 0.0f;
	float defaultWalkSpeed = 1.0f;
	float currentWalkSpeed = defaultWalkSpeed;
	float runSpeed = 100.0f;
};
