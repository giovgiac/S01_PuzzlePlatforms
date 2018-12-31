// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// Engine Includes
#include "Button.h"

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	MenuInterface = Interface;
}

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);

	return true;
}

void UMainMenu::OnHostClicked()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}
