// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "GamePlatform.generated.h"

UENUM(BlueprintType)
enum class EState : uint8 {
	NONE UMETA(DisplayName = "none"),
	RED UMETA(DisplayName = "red"),
	BLUE UMETA(DisplayName = "blue")
};

#define PLATFORM

UCLASS()
class TICTACTOE_API AGamePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePlatform();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Platform;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Box;
public:
	UFUNCTION()
		void Selected();

	// Changes state of this Platform and changes the round
	UFUNCTION(BlueprintCallable)
		void ChangeState();

	// call this function for changing material
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BP_ChangeMaterial();
public:
	UFUNCTION()
	void FromServer();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* StandingPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isOverThisChar = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, replicated)
		EState PlatformState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform number")
		int32 platform_index_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform number")
		int32 platform_index_y;

};