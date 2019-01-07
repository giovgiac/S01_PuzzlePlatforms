// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// Project Includes
#include "MenuInterface.h"
#include "ServerRow.h"

// Engine Includes
#include "Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PanelWidget.h"
#include "TextBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "WidgetSwitcher.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UServerRow> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	ServerList->ClearChildren();
	
	uint32 Index = 0;
	for (auto& Name : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(this, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(Name));
		Row->Setup(this, Index++);

		ServerList->AddChild(Row);
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}

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
	if (!ensure(MenuInterface != nullptr)) return;
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
	MenuInterface->RefreshServerList();
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
	if (!ensure(ServerList != nullptr)) return;

	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index Not Set"));
	}
}
