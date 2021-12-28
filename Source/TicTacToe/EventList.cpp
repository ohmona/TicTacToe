// Fill out your copyright notice in the Description page of Project Settings.


#include "EventList.h"
#include <Kismet/GameplayStatics.h>
#include "TicTacToeGameStateBase.h"
#include "PlayerChar.h"

AEventList::AEventList()
{
}

void AEventList::BeginPlay()
{
	Super::BeginPlay();
	ATicTacToeGameStateBase* state = Cast<ATicTacToeGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	state->EventList = this;
}
void AEventList::PrintLog()
{
	UE_LOG(LogTemp, Log, TEXT("[Event] log"));
}

void AEventList::ReZero(AActor* target)
{
	APlayerChar* p = Cast<APlayerChar>(target);
	if (p != nullptr) {
		p->TeleportTo(FVector(0, 0, 100), FRotator(0, 0, 0));
	}
}