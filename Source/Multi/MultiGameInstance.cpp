// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiGameInstance.h"

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"

#include "PlatformTrigger.h"



UMultiGameInstance::UMultiGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClassBP(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MenuClassBP.Class != NULL)) return;
	MenuClass = MenuClassBP.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuClassBP(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuClassBP.Class != NULL)) return;
	InGameMenuClass = InGameMenuClassBP.Class;
}

void UMultiGameInstance::Init()
{
	
}

//** Add Menu Widget to viewport **//
void UMultiGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(Menu != nullptr)) return;
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

//** Add In Game Menu Widget to viewport **//
void UMultiGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	if (!ensure(InGameMenu != nullptr)) return;
	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

//** Host server **//
void UMultiGameInstance::Host()
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	DebugMessage(TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

//** Join server **//
void UMultiGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	FString JoinMessage = "Joining: " + Address;
	DebugMessage(JoinMessage);

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(World);
	if(!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

//** When loading main menu after exiting in game menu, travel back to MainMenu map which loads ManMenu on beginplay
void UMultiGameInstance::LoadMainMenu()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(World);
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/Maps/L_MainMenu", ETravelType::TRAVEL_Absolute);
}

//** Debugging message to log to screen **//
void UMultiGameInstance::DebugMessage(const FString& Message)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(-1,
		2,
		FColor::Green,
		Message);
}
