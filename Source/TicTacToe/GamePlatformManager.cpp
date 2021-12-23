// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlatformManager.h"
#include <Kismet/GameplayStatics.h>
#include "TicTacToeGameStateBase.h"
#include "Containers/Array.h"

// Sets default values
AGamePlatformManager::AGamePlatformManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	for (int i = 0; i < 3; i++) {
		FYCoordinate dummy;
		dummy.y.Init(0, 3);
		GameArea.Init(dummy, 3);
	}
}

// Called when the game starts or when spawned
void AGamePlatformManager::BeginPlay()
{
	Super::BeginPlay();

	ATicTacToeGameStateBase* Gamestate = Cast<ATicTacToeGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	Gamestate->MainPlatformManager = this;

}

// Called every frame
void AGamePlatformManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGamePlatformManager::AddArea(EState team, int32 x, int32 y)
{
	switch (team) {
	case EState::RED:
		GameArea[x].y[y] = red_team_index;
		UE_LOG(LogTemp, Log, TEXT("RED %d %d : %d"), x, y, GameArea[x].y[y]);
		break;
	case EState::BLUE:
		GameArea[x].y[y] = blue_team_index;
		UE_LOG(LogTemp, Log, TEXT("BLUE %d %d : %d"), x, y, GameArea[x].y[y]);
		break;
	case EState::NONE:
		UE_LOG(LogTemp, Log, TEXT("NONE %d %d : %d"), x, y, GameArea[x].y[y]);
		GameArea[x].y[y] = none_index;
	default:
		break;
	}
}

bool AGamePlatformManager::isSomeoneWon()
{
	int team = 0;
	while (team <= 2) {
		team++;
		int count = 0;
		// 세로 체크
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (GameArea[i].y[j] == team) {
					count++;
				}
			}
			if (count == 3) {
				return true;
			}
			count = 0;
		}
		count = 0;
		// 가로 체크
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (GameArea[j].y[i] == team) {
					count++;
				}
			}
			if (count == 3) {
				return true;
			}
			count = 0;
		}
		count = 0;
		// 대각선 왼쪽아래 오른쪽위 00 11 22
		for (int i = 0; i < 3; i++) {
			if (GameArea[i].y[i] == team) {
				count++;
			}
			if (count >= 3) {
				return true;
			}
		}
		count = 0;
		// 대각선 오른쪽위 왼쪽아래 02 11 20
		int y = 2;
		for (int i = 0; i < 3; i++) {
			if (i == 2) {
				y = 0;
			}
			else if (i == 1) {
				y = 1;
			}

			if (GameArea[i].y[y] == team) {
				count++;
			}

			if (count == 3) {
				return true;
			}
		}
	}
	return false;
}
//hii this is test
