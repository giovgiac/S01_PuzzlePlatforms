// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// Project Includes
#include "MenuInterface.h"

// Engine Includes
#include "Button.h"
#include "EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WidgetSwitcher.h"

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostMainMenuButton != nullptr)) return false;
	HostMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostMainMenuClicked);

	if (!ensure(JoinMainMenuButton != nullptr)) return false;
	JoinMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinMainMenuClicked);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuit);

	if (!ensure(CancelJoinMenuButton != nullptr)) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnCancelJoinMenuClicked);

	if (!ensure(ConfirmJoinMenuButton != nullptr)) return false;
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnConfirmJoinMenuClicked);

	return true;
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

void UMainMenu::OnQuit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);

	/* Alternate Way:
		#if WITH_EDITOR
			UWorld* World = GetWorld();
			if (!ensure(World != nullptr)) return;

			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (!ensure(PlayerController != nullptr)) return;

			PlayerController->ConsoleCommand("quit");
		#else
			FGenericPlatformMisc::RequestExitWithStatus(false, EXIT_SUCCESS);
		#endif
	*/
}

void UMainMenu::OnCancelJoinMenuClicked()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OnConfirmJoinMenuClicked()
{
	if (!ensure(MenuInterface != nullptr)) return;
	if (!ensure(IPAddressField != nullptr)) return;

	const FString& Address = IPAddressField->GetText().ToString();
	MenuInterface->Join(Address);
}
