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
public:
	UFUNCTION(BlueprintCallable, Category = "Head UI")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Head UI")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;
};
