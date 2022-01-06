// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "AimTrigger.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API AAimTrigger : public ATrigger
{
	GENERATED_BODY()

	AAimTrigger();
public:
	USceneComponent* comp;

	void Run() override;

	APlayerChar* clicked_player;
};
