// Fill out your copyright notice in the Description page of Project Settings.

#include "EventList.h"
#include <Kismet/GameplayStatics.h>
#include "TicTacToeGameStateBase.h"
#include "Trigger.h"

AEventList::AEventList()
{
}

void AEventList::RunEvent(EEvent target_event, AActor* trigger, AActor* target)
{
    if (target_event == EEvent::PrintLog) PrintLog();
    if (target_event == EEvent::ReZero) ReZero(target);
    if (target_event == EEvent::RotateCamera) RotateCamera(target); // client
    if (target_event == EEvent::Respawn) Respawn(target);
    if (target_event == EEvent::ShakeCamera) ShakeCamera(target); //client
    if (target_event == EEvent::SetSpawnPoint) SetSpawnPoint(target);

    ATrigger* trig = Cast<ATrigger>(trigger);
    if (trig != nullptr) {
        trig->AfterEvent();
    }
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

void AEventList::RotateCamera(AActor* target)
{
    APlayerChar* p = Cast<APlayerChar>(target);
    if (p != nullptr) {
        FRotator origin = p->GetViewRotation();
        FRotator newRotation = FRotator(origin.Pitch, origin.Yaw, origin.Roll + 20.0f);
        p->GetController()->ClientSetRotation(newRotation);
    }
}

void AEventList::Respawn(AActor* target)
{
    APlayerChar* p = Cast<APlayerChar>(target);
    if (p != nullptr) {
        p->TeleportTo(p->spawn_point, FRotator(0.0f,0.0f,0.0f));
    }
}

void AEventList::SetSpawnPoint(AActor* target)
{
    APlayerChar* p = Cast<APlayerChar>(target);
    if (p != nullptr) {
        p->spawn_point = p->GetActorLocation();
    }
}

void AEventList::ShakeCamera(AActor* target)
{
    APlayerChar* p = Cast<APlayerChar>(target);
    if (p != nullptr) {
        p->BP_ShakeCamera();
    }
}
