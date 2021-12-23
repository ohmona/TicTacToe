// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlatform.h"
#include "GamePlatformManager.h"
#include "GameFramework/GameStateBase.h"
#include "TicTacToeGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToeGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ATicTacToeGameStateBase();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Value")
		EState Round = EState::RED;

	// instance reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		AGamePlatformManager* MainPlatformManager;
};
