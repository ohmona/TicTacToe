// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventList.generated.h"

UCLASS()
class TICTACTOE_API AEventList : public AActor
{
	GENERATED_BODY()
	
public:	
	AEventList();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void PrintLog();

	UFUNCTION(BlueprintCallable)
	void ReZero(AActor* target);
};
