// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

// Project Includes
#include "MenuInterface.h"

// Engine Includes
#include "Button.h"

bool UInGameMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::OnCancelClicked);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::OnQuitClicked);

	return true;
}

void UInGameMenu::OnCancelClicked()
{
	Teardown();
}

void UInGameMenu::OnQuitClicked()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->QuitToMenu();
}
