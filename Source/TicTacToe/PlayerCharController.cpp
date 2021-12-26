// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharController.h"

void APlayerCharController::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("[load] custom controller loaded"));
	FOV(475.0f);
}
