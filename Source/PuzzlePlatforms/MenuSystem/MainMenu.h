// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Project Includes
#include "MenuWidget.h"

// Engine Includes
#include "CoreMinimal.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

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
	class UButton* QuitButton;

	UPROPERTY(meta=(BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta=(BindWidget))
	class UButton* CancelJoinMenuButton;

	UPROPERTY(meta=(BindWidget))
	class UButton* ConfirmJoinMenuButton;

	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* IPAddressField;

private:
	UFUNCTION()
	void OnHostMainMenuClicked();

	UFUNCTION()
	void OnJoinMainMenuClicked();

	UFUNCTION()
	void OnQuit();

	UFUNCTION()
	void OnCancelJoinMenuClicked();

	UFUNCTION()
	void OnConfirmJoinMenuClicked();

};
