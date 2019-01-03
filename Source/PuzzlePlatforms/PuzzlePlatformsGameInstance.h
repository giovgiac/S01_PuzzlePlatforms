// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Project Includes
#include "MenuSystem/MenuInterface.h"

// Engine Includes
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
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
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable, Category=Menu)
	void LoadInGameMenu();

	virtual void Host() override;
	virtual void Join(const FString& Address) override;
	virtual void QuitToMenu() override;
	virtual void RefreshServerList() override;

private:
	TSubclassOf<class UMenuWidget> MenuClass;
	TSubclassOf<class UMenuWidget> InGameMenuClass;

	class UMainMenu* Menu;
	class UMenuWidget* InGameMenu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

private:
	void CreateSession();

	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);
	void OnFindSessionsComplete(bool bSuccess);
};
