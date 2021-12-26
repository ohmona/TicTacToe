// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API APlayerCharController : public APlayerController
{
	GENERATED_BODY()

		virtual void BeginPlay() override;
};
