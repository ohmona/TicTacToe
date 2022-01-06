// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerChar.h"
#include "GameFramework/Actor.h"
#include "PlayerChar.h"
#include "EventList.generated.h"

UENUM(BlueprintType)
enum class EEvent : uint8 {
    PrintLog UMETA(DisplayName = "PringLog"),
    ReZero UMETA(DisplayName = "ReZero"),
    RotateCamera UMETA(DisplayName = "RotateCamera"),
    Respawn UMETA(DisplayName = "Respawn"),
    SetSpawnPoint UMETA(Displayname = "SetSpawnPoint"),
    ShakeCamera UMETA(Displayname = "ShakeCamera")
};
// 1. 함수 구현
// 2. 열거형에 등록
// 3. RunEvent 에 추가
//
// 5. 쓸땐 events->RunEvent(desired_event, target)
//    혹은 events->RunEvent(desired_event, nullptr)

UCLASS()
class TICTACTOE_API AEventList : public AActor
{
    GENERATED_BODY()

public:
    AEventList();

    void RunEvent(EEvent target_event, AActor* trigger, AActor* target);

protected:
    virtual void BeginPlay() override;

public:
    void PrintLog();
    void ReZero(AActor* target);
    void RotateCamera(AActor* target);
    void Respawn(AActor* target);
    void SetSpawnPoint(AActor* target);
    void ShakeCamera(AActor* target);
};