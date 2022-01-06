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

	virtual void Landed(const FHitResult& Result) override;

// Components
public:
	UPROPERTY(BlueprintReadWrite)
	class UPlayerCharMovementComponent* Movement;

	class UCharacterMovementComponent* BaseMovement;

// Functions for ownership
public:

	UFUNCTION(Server, Unreliable)
		void AsServer();

public:
	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BP_playWinEffect(const EState winner);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ShakeCamera();

	void ResetCamera();
	void CalcSpeed();
	void TpLevel(FName level);

// Movements
public:
	UFUNCTION(BlueprintCallable) void MoveForward(float AxisValue);
	UFUNCTION(BlueprintCallable) void MoveRight(float AxisValue);

	UFUNCTION(BlueprintCallable) void Turn(float AxisValue);
	UFUNCTION(BlueprintCallable) void Lookup(float AxisValue);

	UFUNCTION(BlueprintCallable) void Select();

	UFUNCTION(BlueprintCallable) void StartJump();
	UFUNCTION(BlueprintCallable) void StopJump();

	UFUNCTION(BlueprintCallable, Server, Unreliable) void StartSprint(); void CLStartSprint();
	UFUNCTION(BlueprintCallable, Server, Unreliable) void StopSprint(); void CLStopSprint();

	UFUNCTION(BlueprintCallable, Server, Unreliable) void StartSneak(); void CLStartSneak();
	UFUNCTION(BlueprintCallable, Server, Unreliable) void StopSneak(); void CLStopSneak();

	UFUNCTION(BlueprintCallable) FHitResult GetActorInAim();

	void OnStanding();
public:
	float time = 0.0f;
	bool timerrun = false;

	float origin_pitch;
	float origin_yaw;

	FTimerHandle timer;

	void RotateCam();

public:
	UPROPERTY(EditAnywhere)
		USoundBase* landing_sound;

	UPROPERTY(EditAnywhere)
		USoundBase* sneaking_sound;

public:
	UPROPERTY(BlueprintReadWrite)
		FName LevelName;

	UPROPERTY(BlueprintReadWrite)
		FString user_name = FString(TEXT("USER_NAME"));

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mouse")
		float ClickRange = 10000.0f;

	// on platform!!
	UPROPERTY(BlueprintReadWrite)
		bool isStandingOver = false;

	UPROPERTY(BlueprintReadWrite)
		bool isCrouching = false;

	// generally standing!!
	UPROPERTY(BlueprintReadWrite)
		bool isNOTStanding = false;

	UPROPERTY(BlueprintReadWrite)
		AGamePlatform* StandingPlatform;

	UPROPERTY(BlueprintReadWrite)
	FVector spawn_point;
};
