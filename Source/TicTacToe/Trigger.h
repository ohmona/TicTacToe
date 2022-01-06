// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharController.h"
#include "EventList.h"
#include "Trigger.generated.h"

UCLASS()
class TICTACTOE_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AfterEvent();

	virtual void Run();

	APlayerCharController* ctr();

public:
	UPROPERTY(BlueprintReadOnly)
	AEventList* events;

	UPROPERTY(BlueprintReadWrite)
	int32 count = 0;

	UPROPERTY(BlueprintReadWrite)
	AActor* latest_target;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEvent desired_event = EEvent::PrintLog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEnable = true;
};
