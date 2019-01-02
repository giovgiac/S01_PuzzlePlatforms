// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

// Engine Includes
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSubsystem.h"
#include "UObject/ConstructorHelpers.h"

// Project Includes
#include "MenuSystem/MenuWidget.h"
#include "PlatformTrigger.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UMenuWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;

	static ConstructorHelpers::FClassFinder<UMenuWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	InGameMenuClass = InGameMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found online subsystem %s"), *Subsystem->GetSubsystemName().ToString());

		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session interface"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMenuWidget>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;
	
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr)) return;

	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/Puzzle?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::QuitToMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}
