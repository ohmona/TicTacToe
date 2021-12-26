// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Movement = CreateDefaultSubobject<UPlayerCharMovementComponent>(TEXT("Custom movement component"));
	Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->UpdatedComponent = RootComponent;
	Movement->CrouchedHalfHeight = CrouchScale;
	Movement->JumpZVelocity = JumpScale;


}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("[Load] Player Char"));
	UE_LOG(LogTemp, Log, TEXT("[prof] Speed : %f"), DefaultSpeed);
	UE_LOG(LogTemp, Log, TEXT("[prof] Jump ability : %f"), JumpScale);
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

	UE_LOG(LogTemp, Log, TEXT("[fun] setup input component"));
	InputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	InputComponent->BindAxis("Turn", this, &APlayerChar::Turn);
	InputComponent->BindAxis("Lookup", this, &APlayerChar::Lookup);

	InputComponent->BindAction("Select",IE_Released, this, &APlayerChar::Select);

	InputComponent->BindAction("Jump",IE_Pressed, this, &APlayerChar::StartJump);
	InputComponent->BindAction("Jump",IE_Released, this, &APlayerChar::StopJump);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerChar::CLStartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerChar::CLStopSprint);

	InputComponent->BindAction("Sneak", IE_Pressed, this, &APlayerChar::CLStartSneak);
	InputComponent->BindAction("Sneak", IE_Released, this, &APlayerChar::CLStopSneak);
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

void APlayerChar::ReturnToMainMenu() 
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainMenu")));
}


//
// Movement
//
void APlayerChar::MoveForward(float AxisValue)
{
	if (Movement && (Movement->UpdatedComponent == RootComponent)) {
		AddMovementInput(GetActorForwardVector(), AxisValue, true);
	}
}

void APlayerChar::MoveRight(float AxisValue)
{
	if (Movement && (Movement->UpdatedComponent == RootComponent)) {
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void APlayerChar::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue * Sensitivity);
}

void APlayerChar::Lookup(float AxisValue)
{
	AddControllerPitchInput(AxisValue * Sensitivity);
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

// SPRINT
void APlayerChar::CLStartSprint()
{
	Movement->MaxWalkSpeed = SprintSpeed;
	StartSprint();
}
void APlayerChar::StartSprint_Implementation()
{
	Movement->MaxWalkSpeed = SprintSpeed;
}

void APlayerChar::CLStopSprint()
{
	Movement->MaxWalkSpeed = DefaultSpeed;
	StopSprint();
}
void APlayerChar::StopSprint_Implementation()
{
	Movement->MaxWalkSpeed = DefaultSpeed;
}

// SNEAK
void APlayerChar::CLStartSneak()
{
	if (!isCrouching) {
		isCrouching = true;
		SetActorLocation(FVector(
			GetActorLocation().X,
			GetActorLocation().Y,
			GetActorLocation().Z + CrouchScale
		));
		Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
		Crouch();
	}
	StartSneak();
}
void APlayerChar::StartSneak_Implementation()
{
	if (!isCrouching) {
		isCrouching = true;
		SetActorLocation(FVector(
			GetActorLocation().X,
			GetActorLocation().Y,
			GetActorLocation().Z + CrouchScale
		));
		Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
		Crouch();
	}
}

void APlayerChar::CLStopSneak()
{
	isCrouching = false;

	UnCrouch();
	StopSneak();
}
void APlayerChar::StopSneak_Implementation()
{
	isCrouching = false;
	
	UnCrouch();
}

// 
//	SERVER
//

void APlayerChar::AsServer_Implementation()
{
	StandingPlatform->FromServer();
}
