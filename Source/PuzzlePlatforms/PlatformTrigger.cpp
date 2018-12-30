// Fill out your copyright notice in the Description page of Project Settings.

// Project Includes
#include "PlatformTrigger.h"

// Engine Includes
#include "Components/BoxComponent.h"

APlatformTrigger::APlatformTrigger()
{
	// Set Defaults
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	if (!ensure(TriggerVolume)) return;

	RootComponent = TriggerVolume;
}

void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

