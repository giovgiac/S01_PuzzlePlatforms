// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// Engine Includes
#include "Button.h"

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	MenuInterface = Interface;
}

void UMainMenu::Setup()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetWidgetToFocus(TakeWidget());

	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(InputModeData);

	AddToViewport();
}

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);

	return true;
}

// ALTERNATIVE: Use a Teardown method and call it from the GameInstance
void UMainMenu::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(InputModeData);

	RemoveFromViewport();
}

void UMainMenu::OnHostClicked()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}
