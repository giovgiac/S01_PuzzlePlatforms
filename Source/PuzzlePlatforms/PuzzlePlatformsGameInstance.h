// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category=Menu)
	void LoadMenu();

	UFUNCTION(BlueprintCallable, Category=Menu)
	void LoadInGameMenu();

	virtual void Host() override;
	virtual void Join(const FString& Address) override;
	virtual void QuitToMenu() override;

private:
	TSubclassOf<class UMenuWidget> MenuClass;
	TSubclassOf<class UMenuWidget> InGameMenuClass;

	class UMenuWidget* Menu;
	class UMenuWidget* InGameMenu;
};
