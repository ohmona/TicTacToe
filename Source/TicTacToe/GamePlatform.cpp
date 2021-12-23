// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlatform.h"
#include <Runtime/Engine/Classes/Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include "TicTacToeGameStateBase.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>
#include <TicTacToe/PlayerChar.h>

// Sets default values
AGamePlatform::AGamePlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	PlatformState = EState::NONE;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Rootcomponent");

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	Box->SetupAttachment(RootComponent);

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGamePlatform::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGamePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGamePlatform::ChangeState()
{
	UE_LOG(LogTemp, Log, TEXT("ChangeState() entry"));
	ATicTacToeGameStateBase* Gamestate = Cast<ATicTacToeGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	
	if (Gamestate != nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Platformstate : %d"), static_cast<EState>(PlatformState));
		UE_LOG(LogTemp, Log, TEXT("Round : %d"), static_cast<EState>(Gamestate->Round));
		switch (PlatformState) {
		case EState::NONE:
			switch (Gamestate->Round) {
			case EState::RED:
				Gamestate->Round = EState::BLUE;
				PlatformState = EState::RED;
				break;
			case EState::BLUE:
				Gamestate->Round = EState::RED;
				PlatformState = EState::BLUE;
				break;
			default:
				Gamestate->Round = EState::BLUE;
				PlatformState = EState::RED;
				break;
			}
			break;
		case EState::BLUE:
			PlatformState = EState::NONE;
			break;
		case EState::RED:
			PlatformState = EState::NONE;
			break;
		}
		BP_ChangeMaterial();
		Gamestate->MainPlatformManager->AddArea(PlatformState, platform_index_x, platform_index_y);
		UE_LOG(LogTemp, Log, TEXT("ChangeState() ending"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Gamestate is NULL"));
	}
}

void AGamePlatform::Selected() 
{
	APlayerChar* p = Cast<APlayerChar>(StandingPawn);
	if (p != nullptr) {
		p->AsServer();
	}
}
//
//	SERVER
//
void AGamePlatform::FromServer()
{
	ChangeState();

	// check whether someone has won
	ATicTacToeGameStateBase* Gamestate = Cast<ATicTacToeGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	Gamestate->MainPlatformManager->onWin();
}

void AGamePlatform::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(AGamePlatform, PlatformState);
}