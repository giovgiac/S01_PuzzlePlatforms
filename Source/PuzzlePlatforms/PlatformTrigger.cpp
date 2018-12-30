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

	// Add Callbacks
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activated"));
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivated"));
}

