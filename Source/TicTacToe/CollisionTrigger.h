// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trigger.h"
#include "CollisionTrigger.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ACollisionTrigger : public ATrigger
{
	GENERATED_BODY()

	ACollisionTrigger();

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	bool activate_twice = false;
};