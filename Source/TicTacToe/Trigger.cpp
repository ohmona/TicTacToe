// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"
#include <Kismet/GameplayStatics.h>
#include <TicTacToe/TicTacToeGameStateBase.h>

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	ATicTacToeGameStateBase* state = Cast<ATicTacToeGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	events = state->EventList;
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrigger::Run()
{
}

APlayerCharController* ATrigger::ctr()
{
	return Cast<APlayerCharController>(GetWorld()->GetFirstPlayerController());
}