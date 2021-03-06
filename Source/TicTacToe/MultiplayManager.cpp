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
	levels.Add("Island");
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
	APlayerChar* p = Cast<APlayerChar>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (p != nullptr) {
		p->LevelName = level;
	}

	UE_LOG(LogTemp, Log, TEXT("[fun] hostgame"));
	if (use_lan) { // host game using lan
		BP_OpenGameLan(level);
	}
	else { // host game using ip
		FName* cmd = new FName("open " + level.ToString() + "?listen");
		BP_OpenGameIp(*cmd);
	}
	UserJoind();
}

// join the ip game
void AMultiplayManager::JoinGameIp(FName adress)
{
	BP_JoinGameIp(adress);
	UserJoind();
}

// join the lan game
void AMultiplayManager::JoinGameLan()
{
	BP_JoinGameLan();
	UserJoind();
}

void AMultiplayManager::UserJoind_Implementation()
{
	session_info.user_count += 1;
}

void AMultiplayManager::StartGame()
{
	APlayerChar* p = Cast<APlayerChar>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (p != nullptr) {
		p->TpLevel(p->LevelName);
	}
}