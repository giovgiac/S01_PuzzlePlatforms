// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category=Movement)
	float Speed = 20.0f;

	UPROPERTY(EditAnywhere, Category=Movement, meta=(MakeEditWidget=true))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
};
