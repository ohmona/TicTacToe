// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTrigger.h"

ACollisionTrigger::ACollisionTrigger()
{
	RootComponent = CreateDefaultSubobject<UBoxComponent>("Rootcomponent");
}

void ACollisionTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (isEnable) {
		events->RunEvent(desired_event, this, OtherActor);
	}
}

void ACollisionTrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (activate_twice && isEnable) {
		events->RunEvent(desired_event ,this , OtherActor);
	}
}