// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// Engine Includes
#include "Button.h"
#include "WidgetSwitcher.h"

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

	if (!ensure(HostMainMenuButton != nullptr)) return false;
	HostMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostMainMenuClicked);

	if (!ensure(JoinMainMenuButton != nullptr)) return false;
	JoinMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinMainMenuClicked);

	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnCancelJoinMenuClicked);

	if (!ensure(JoinJoinMenuButton != nullptr)) return false;
	JoinJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinJoinMenuClicked);

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

void UMainMenu::OnHostMainMenuClicked()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->Host();
}

void UMainMenu::OnJoinMainMenuClicked()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OnCancelJoinMenuClicked()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OnJoinJoinMenuClicked()
{

}


