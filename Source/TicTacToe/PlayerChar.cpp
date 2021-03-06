// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include <Kismet/GameplayStatics.h>
#include <TicTacToe/Trigger.h>
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>
#include <TicTacToe/AimTrigger.h>

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMovement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement = CreateDefaultSubobject<UPlayerCharMovementComponent>(TEXT("MovComp"));

	BaseMovement->CrouchedHalfHeight = CrouchScale;
	BaseMovement->JumpZVelocity = JumpScale;
	BaseMovement->MaxWalkSpeed = DefaultSpeed;

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("[Load] Player Char"));
	UE_LOG(LogTemp, Log, TEXT("[prof] Speed : %f"), DefaultSpeed);
	UE_LOG(LogTemp, Log, TEXT("[prof] Jump ability : %f"), JumpScale);

	spawn_point = GetActorLocation();
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetActorLocation().Z < -10000) {
		TeleportTo(spawn_point, GetActorRotation());
	}
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

void APlayerChar::Landed(const FHitResult& Result)
{
	BP_ShakeCamera();
	UGameplayStatics::PlaySound2D(GetWorld(), landing_sound, 1, 1, 0);
}

void APlayerChar::ReturnToMainMenu() 
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainMenu")));
}

FHitResult APlayerChar::GetActorInAim()
{
	FVector rayLocation;
	FRotator rayRotation;
	FVector endTrace = FVector::ZeroVector;

	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();

	if (playerController)
	{
		playerController->GetPlayerViewPoint(rayLocation, rayRotation);
		endTrace = rayLocation + (rayRotation.Vector() * ClickRange);
	}

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(GetActorInAim), true, GetInstigator());
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endTrace, ECC_Visibility, traceParams);

	return hit;
}

//
// Movement
//
void APlayerChar::MoveForward(float AxisValue)
{
	if (Movement && (Movement->UpdatedComponent == RootComponent)) {
		Movement->walkForwardAxisValue = AxisValue;
	}
}

void APlayerChar::MoveRight(float AxisValue)
{
	if (Movement && (Movement->UpdatedComponent == RootComponent)) {
		Movement->walkRightAxisValue = AxisValue;
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
	AActor* aim_actor = Cast<AActor>(GetActorInAim().GetActor());
	if (aim_actor) {
		AAimTrigger* aim = Cast<AAimTrigger>(aim_actor);
		if (aim) {
			aim->clicked_player = this;
			aim->Run();
		}
		APlayerChar* ply = Cast<APlayerChar>(aim_actor);
		if (ply) {
			ply->AddMovementInput(ply->GetActorForwardVector(), -1, true);
			ply->BP_ShakeCamera();
			UE_LOG(LogTemp, Log, TEXT("Se"));
		}
	}

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
	isNOTStanding = true;
}
void APlayerChar::StopJump()
{
	bPressedJump = false;
}

// SPRINT
void APlayerChar::CLStartSprint()
{
	BaseMovement->MaxWalkSpeed = SprintSpeed;
	StartSprint();
}
void APlayerChar::StartSprint_Implementation()
{
	BaseMovement->MaxWalkSpeed = SprintSpeed;
}

void APlayerChar::CLStopSprint()
{
	BaseMovement->MaxWalkSpeed = DefaultSpeed;
	StopSprint();
}
void APlayerChar::StopSprint_Implementation()
{
	BaseMovement->MaxWalkSpeed = DefaultSpeed;
}

// SNEAK
void APlayerChar::CLStartSneak()
{
	StartSneak();

	Movement->bPressedSneak = true;
	UGameplayStatics::PlaySound2D(GetWorld(), sneaking_sound, 1, 1, 0);

	if (!GetVelocity().IsNearlyZero()) {
		CalcSpeed();

		time = 0.0f;
		timerrun = true;

		Movement->wasRunning = true;

		GetWorldTimerManager().SetTimer(timer, this, &APlayerChar::RotateCam, 0.01f, true, 0.0f);
	}
}

void APlayerChar::RotateCam()
{
	if (timerrun) {
		FRotator origin = GetViewRotation();
		origin_pitch = GetViewRotation().Pitch;
		origin_yaw = GetViewRotation().Yaw;

		if (time < 0.5) {
			GetController()->ClientSetRotation(FRotator(origin.Pitch, origin.Yaw, (origin.Roll + 0.2f)));
		}
		time += 0.01f;
		if (time == 0.5f) {
			timerrun = false;
			time = 0.0f;
		}
	}
}

void APlayerChar::ResetCamera()
{
	GetController()->ClientSetRotation(FRotator(
		origin_pitch, origin_yaw, 0.0f));
}

void APlayerChar::CalcSpeed()
{
	if (BaseMovement->MaxWalkSpeed >= SprintSpeed) {
		// sprinting + sneaking
		BaseMovement->MaxWalkSpeed = SprintSpeed * 1.5f;
		BaseMovement->MaxWalkSpeedCrouched = BaseMovement->MaxWalkSpeed;
	}
	else {
		// walking + sneaking
		BaseMovement->MaxWalkSpeed = 900.0f; // 900
		BaseMovement->MaxWalkSpeedCrouched = BaseMovement->MaxWalkSpeed;
	}
}

void APlayerChar::StartSneak_Implementation()
{
	Movement->bPressedSneak = true;

	if (!GetVelocity().IsNearlyZero()) {
		CalcSpeed();

		Movement->wasRunning = true;
	}
}

void APlayerChar::CLStopSneak()
{
	BaseMovement->MaxWalkSpeed = DefaultSpeed;
	Movement->bPressedSneak = false;
}

void APlayerChar::StopSneak_Implementation()
{
	isCrouching = false;
	
	UnCrouch();
}

void APlayerChar::OnStanding()
{

}

void APlayerChar::TpLevel(FName level)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *level.ToString())
	UGameplayStatics::OpenLevel(GetWorld(), level);
}
// 
//	SERVER
//

void APlayerChar::AsServer_Implementation()
{
	StandingPlatform->FromServer();
}