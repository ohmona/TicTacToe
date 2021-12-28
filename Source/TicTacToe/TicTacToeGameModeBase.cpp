// Copyright Epic Games, Inc. All Rights Reserved.


#include "TicTacToeGameModeBase.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

void ATicTacToeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATicTacToeGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr) 
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
			if (CurrentWidget != nullptr)
			{
				CurrentWidget->AddToViewport();
			}
	}
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->bShowMouseCursor = true;
	controller->SetInputMode(FInputModeGameAndUI());
}