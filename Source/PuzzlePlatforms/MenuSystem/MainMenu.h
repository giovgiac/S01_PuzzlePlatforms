// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* Interface);
	void Setup();

protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta=(BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta=(BindWidget))
	class UButton* HostMainMenuButton;

	UPROPERTY(meta=(BindWidget))
	class UButton* JoinMainMenuButton;

	UPROPERTY(meta=(BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta=(BindWidget))
	class UButton* CancelJoinMenuButton;

	UPROPERTY(meta=(BindWidget))
	class UButton* JoinJoinMenuButton;

	IMenuInterface* MenuInterface;

private:
	UFUNCTION()
	void OnHostMainMenuClicked();

	UFUNCTION()
	void OnJoinMainMenuClicked();

	UFUNCTION()
	void OnCancelJoinMenuClicked();

	UFUNCTION()
	void OnJoinJoinMenuClicked();

};
