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
	UFUNCTION(BlueprintCallable)
		void QuitGame();
	// continue
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void ContinueGame();
public:
	// host
	UFUNCTION(BlueprintCallable)
		void HostGame(bool use_lan, const FName level);
	
	UFUNCTION(BlueprintImplementableEvent) void BP_OpenGameLan(const FName level);
	UFUNCTION(BlueprintImplementableEvent) void BP_OpenGameIp(const FName cmd);
	
	// join
	// ip
	UFUNCTION(BlueprintCallable)
		void JoinGameIp(FName adress);
	UFUNCTION(BlueprintImplementableEvent) void BP_JoinGameIp(const FName adress);
	// lan
	UFUNCTION(BlueprintCallable)
		void JoinGameLan();
	UFUNCTION(BlueprintImplementableEvent) void BP_JoinGameLan();
public:
	// level array
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> levels;
};
