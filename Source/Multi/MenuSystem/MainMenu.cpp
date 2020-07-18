// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "GenericPlatform/GenericPlatformMisc.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(BackButton != nullptr)) return false;
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinGameButton != nullptr)) return false;
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(ExitApplicationButton != nullptr)) return false;
	ExitApplicationButton->OnClicked.AddDynamic(this, &UMainMenu::ExitApplication);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	SwitchMenu(MenuSwitcher, JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	SwitchMenu(MenuSwitcher, MainMenu);
}

void UMainMenu::SwitchMenu(UWidgetSwitcher* WidgetSwitcher, UWidget* MenuToSwitchTo)
{
	if (!ensure(WidgetSwitcher != nullptr)) return;
	if (!ensure(MenuToSwitchTo != nullptr)) return;
	WidgetSwitcher->SetActiveWidget(MenuToSwitchTo);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		if (!ensure(IPAddressField != nullptr)) return;
		const FString& IPAddress = IPAddressField->GetText().ToString();
		MenuInterface->Join(IPAddress);
	}
}

void UMainMenu::ExitApplication()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}