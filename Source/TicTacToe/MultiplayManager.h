// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultiplayManager.generated.h"

UCLASS()
class TICTACTOE_API AMultiplayManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiplayManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// quit
	// continue
public:
	// host
		// ip
		// lan
	// join
		// ip
		// lan
public:
	// hide cursor
public:
	// level array
};
