// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlatform.h"
#include "GameFramework/Character.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "PlayerChar.generated.h"

UCLASS()
class TICTACTOE_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

// Functions for ownership
public:

	UFUNCTION(Server, Unreliable)
		void AsServer();

public:
	UFUNCTION()
		void MoveForward(float AxisValue);

	UFUNCTION()
		void MoveRight(float AxisValue);

	void Select();

	void StartJump();
	void StopJump();

	void StartSprint();
	void StopSprint();

	void StartSneak();
	void StopSneak();

public:
	UPROPERTY(EditAnywhere, Category = "Movement")
		float DefaultSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float SprintSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float CrouchScale = 100.0f;

	UPROPERTY(BlueprintReadWrite)
		bool isStandingOver = false;

	UPROPERTY(BlueprintReadWrite)
		AGamePlatform* StandingPlatform;

public:
	UCharacterMovementComponent* Movement;
};
