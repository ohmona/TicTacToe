// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamePlatform.h"
#include "GamePlatformManager.generated.h"

USTRUCT()
struct FYCoordinate {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		TArray<int32> y;
};

UCLASS()
class TICTACTOE_API AGamePlatformManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePlatformManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void AddArea(EState team, int32 x, int32 y);

	UFUNCTION(Category = "gamemode", BlueprintCallable)
		bool isSomeoneWon();

	UFUNCTION(Category = "gamemode", BlueprintImplementableEvent, BlueprintCallable)
		void onWin();

	UPROPERTY(VisibleAnywhere)
		int32 none_index = 0;

	UPROPERTY(EditAnywhere)
		int32 red_team_index = 1;

	UPROPERTY(EditAnywhere)
		int32 blue_team_index = 2;

	TArray<FYCoordinate> GameArea;
};
