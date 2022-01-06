// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamePlatformManager.h"
#include "TicTacToeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

};
