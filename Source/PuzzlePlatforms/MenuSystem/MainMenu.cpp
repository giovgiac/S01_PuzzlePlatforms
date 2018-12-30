// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

// Engine Includes
#include "Button.h"

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostClicked);

	return true;
}

void UMainMenu::OnHostClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server!"));
}
