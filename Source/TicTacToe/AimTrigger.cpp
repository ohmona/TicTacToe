// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrigger.h"

AAimTrigger::AAimTrigger()
{
	comp = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = comp;
}

void AAimTrigger::Run()
{
	if (isEnable) {
		if (clicked_player) {
			ctr()->ExecuteEventServer(desired_event, this, clicked_player);
		}
	}
}
