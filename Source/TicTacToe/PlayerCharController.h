// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <TicTacToe/EventList.h>
#include "PlayerCharController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API APlayerCharController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(Client, unreliable, BlueprintCallable)
	void onGameStart();

// EVENT
public:
	UFUNCTION(Server, Unreliable)
		void ExecuteEventServer(EEvent target_event, AActor* trigger, AActor* target);

private:
	UFUNCTION(NetMulticast, Unreliable)
		void ExecuteEventMultiple(EEvent target_event, AActor* trigger, AActor* target);

// WIDGET
public:
	UFUNCTION(Client, unreliable, BlueprintCallable, Category = "Head UI")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(Client, unreliable, BlueprintCallable, Category = "Head UI")
		void ChangeUiWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(Client, unreliable, BlueprintCallable, Category = "Head UI")
		void AddWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(Client, unreliable, BlueprintCallable, Category = "Head UI")
		void ClearWidget();

	UFUNCTION(Client, unreliable, BlueprintCallable, Category = "Head UI")
		void RemoveWidget(TSubclassOf<UUserWidget> NewWidgetClass);

private:
	UPROPERTY()
		TArray<UUserWidget*> Widgets;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "settings")
		float fov_value = 475.0f;
};
