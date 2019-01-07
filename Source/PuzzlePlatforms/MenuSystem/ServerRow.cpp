// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"

// Project Includes
#include "MainMenu.h"

// Engine Includes
#include "Button.h"

void UServerRow::Setup(UMainMenu* Parent, uint32 Index)
{
	this->Parent = Parent;
	this->Index = Index;

	if (!ensure(ServerButton != nullptr)) return;
	this->ServerButton->OnClicked.AddDynamic(this, &UServerRow::OnServerButtonClicked);
}

void UServerRow::OnServerButtonClicked()
{
	if (!ensure(Parent != nullptr)) return;

	Parent->SelectIndex(Index);
}
