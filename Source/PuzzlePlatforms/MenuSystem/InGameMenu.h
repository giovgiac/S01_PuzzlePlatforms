// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Project Includes
#include "MenuWidget.h"

// Engine Includes
#include "CoreMinimal.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY(meta=(BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta=(BindWidget))
	class UButton* QuitButton;

private:
	UFUNCTION()
	void OnCancelClicked();

	UFUNCTION()
	void OnQuitClicked();
};
