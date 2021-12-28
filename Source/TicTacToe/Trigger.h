// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	// use if only event execution needed
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void onSelected();

	// use if specific target needed, set history if needed
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void onSelected_target(AActor* target);

	UPROPERTY(BlueprintReadOnly)
	AEventList* events;

	UPROPERTY(BlueprintReadWrite)
	int32 count = 0;

	UPROPERTY(BlueprintReadWrite)
	AActor* latest_target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEnable = true;;
};
