// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayManager.h"
#include "TicTacToeGameStateBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMultiplayManager::AMultiplayManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	levels.Add("Default");
	levels.Add("Room");
}

// Called when the game starts or when spawned
void AMultiplayManager::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("[Load] Multiplayer Manager"));

	ATicTacToeGameStateBase* Gamestate = Cast<ATicTacToeGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	Gamestate->MainMultiplayManager = this;
}

// Called every frame
void AMultiplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// quit the game
void AMultiplayManager::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}

// host the game
void AMultiplayManager::HostGame(bool use_lan, FName level)
{
	UE_LOG(LogTemp, Log, TEXT("[fun] hostgame"));
	if (use_lan) { // host game using lan
		BP_OpenGameLan(level);
	}
	else { // host game using ip
		FName* cmd = new FName("open " + level.ToString() + "?listen");
		BP_OpenGameIp(*cmd);
	}
}

// join the ip game
void AMultiplayManager::JoinGameIp(FName adress)
{
	BP_JoinGameIp(adress);
}

// join the lan game
void AMultiplayManager::JoinGameLan()
{
	BP_JoinGameLan();
}