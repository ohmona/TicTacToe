// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Movement = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	Movement->CrouchedHalfHeight = CrouchScale;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Ihr lernt zu ungenau"));
	UE_LOG(LogTemp, Log, TEXT("Speed : %f"), DefaultSpeed);
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);
	InputComponent->BindAxis("Lookup", this, &APlayerChar::AddControllerPitchInput);

	InputComponent->BindAction("Select",IE_Released, this, &APlayerChar::Select);

	InputComponent->BindAction("Jump",IE_Pressed, this, &APlayerChar::StartJump);
	InputComponent->BindAction("Jump",IE_Released, this, &APlayerChar::StopJump);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerChar::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerChar::StopSprint);

	InputComponent->BindAction("Sneak", IE_Pressed, this, &APlayerChar::StartSneak);
	InputComponent->BindAction("Sneak", IE_Released, this, &APlayerChar::StopSneak);
}

void APlayerChar::NotifyActorBeginOverlap(AActor* OtherActor)
{
	StandingPlatform = Cast<AGamePlatform>(OtherActor);
	if (StandingPlatform != nullptr) {
		StandingPlatform->isOverThisChar = true;
		isStandingOver = true;
		StandingPlatform->StandingPawn = this;
	}
}

void APlayerChar::NotifyActorEndOverlap(AActor* OtherActor)
{
	StandingPlatform = Cast<AGamePlatform>(OtherActor);
	if (StandingPlatform != nullptr) {
		StandingPlatform->isOverThisChar = false;
		isStandingOver = false;
		StandingPlatform->StandingPawn = nullptr;
	}
}

void APlayerChar::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void APlayerChar::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void APlayerChar::Select()
{
	if (isStandingOver) {
		UE_LOG(LogTemp, Log, TEXT("Selection onside"));
		StandingPlatform->Selected();
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Selection outside"));
	}
}

void APlayerChar::StartJump()
{
	bPressedJump = true;
}
void APlayerChar::StopJump()
{
	bPressedJump = false;
}

void APlayerChar::StartSprint()
{
	Movement->MaxWalkSpeed = SprintSpeed;
}
void APlayerChar::StopSprint()
{
	Movement->MaxWalkSpeed = DefaultSpeed;
}

void APlayerChar::StartSneak()
{
	Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
	Crouch();
}

void APlayerChar::StopSneak()
{
	UnCrouch();
}

// 
//	SERVER
//
void APlayerChar::AsServer_Implementation()
{
	StandingPlatform->FromServer();
}

