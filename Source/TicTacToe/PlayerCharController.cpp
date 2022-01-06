// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharController.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include <TicTacToe/Trigger.h>


void APlayerCharController::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("[load] custom controller loaded"));
}

void APlayerCharController::Tick(float DeltaTime)
{
	FOV(fov_value);
}

void APlayerCharController::onGameStart_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[load] GameStarted as client"));
}
//
// EVENTS
//
void APlayerCharController::ExecuteEventServer_Implementation(EEvent target_event, AActor* trigger, AActor* target)
{
	ATrigger* trig = Cast<ATrigger>(trigger);
	if (trig != nullptr) {
		trig->events->RunEvent(target_event, trigger, target);
	}
	ExecuteEventMultiple(target_event, trigger, target);
}
void APlayerCharController::ExecuteEventMultiple_Implementation(EEvent target_event, AActor* trigger, AActor* target)
{
	ATrigger* trig = Cast<ATrigger>(trigger);
	if (trig != nullptr) {
		trig->events->RunEvent(target_event, trigger, target);
	}
}


//
// WIDGETS
//
void APlayerCharController::ChangeMenuWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass)
{
	ClearWidget();

	AddWidget(NewWidgetClass);

	this->bShowMouseCursor = true;
	this->SetInputMode(FInputModeGameAndUI());
}

void APlayerCharController::ChangeUiWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass)
{
	ClearWidget();

	AddWidget(NewWidgetClass);

	this->bShowMouseCursor = false;
	this->SetInputMode(FInputModeGameOnly());
}

void APlayerCharController::AddWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (NewWidgetClass != nullptr)
	{
		UUserWidget* CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void APlayerCharController::ClearWidget_Implementation()
{
	for (int i = 0; i < Widgets.Num(); i++)
	{
		if (Widgets[i] != nullptr)
		{
			Widgets[i]->RemoveFromParent();
			Widgets[i] = nullptr;
		}
	}
}

void APlayerCharController::RemoveWidget_Implementation(TSubclassOf<UUserWidget> NewWidgetClass)
{
	for (int i = 0; i < Widgets.Num(); i++)
	{
		if (Widgets[i] != nullptr)
		{
			if (Widgets[i]->IsA(NewWidgetClass)) {
				Widgets[i]->RemoveFromParent();
				Widgets[i] = nullptr;
			}
		}
	}
}