// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlatform.h"
#include "GameFramework/Character.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <TicTacToe/PlayerCharMovementComponent.h>
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

// Components
public:
	class UCharacterMovementComponent* Movement;

// Functions for ownership
public:

	UFUNCTION(Server, Unreliable)
		void AsServer();

public:
	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BP_playWinEffect(const EState winner);

// Movements
public:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void Turn(float AxisValue);
	void Lookup(float AxisValue);

	void Select();

	void StartJump();
	void StopJump();

	UFUNCTION(Server, Unreliable) void StartSprint(); void CLStartSprint();
	UFUNCTION(Server, Unreliable) void StopSprint(); void CLStopSprint();

	UFUNCTION(Server, Unreliable) void StartSneak(); void CLStartSneak();
	UFUNCTION(Server, Unreliable) void StopSneak(); void CLStopSneak();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float DefaultSpeed = 600.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float SprintSpeed = 1200.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float CrouchScale = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		float JumpScale = 500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mouse")
		float Sensitivity = 1.0f;

	UPROPERTY(BlueprintReadWrite)
		bool isStandingOver = false;

	UPROPERTY(BlueprintReadWrite)
		bool isCrouching = false;

	UPROPERTY(BlueprintReadWrite)
		AGamePlatform* StandingPlatform;
};
