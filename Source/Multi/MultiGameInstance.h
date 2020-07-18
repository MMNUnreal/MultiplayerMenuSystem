// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "MultiGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTI_API UMultiGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

private:
	UMultiGameInstance(const FObjectInitializer& ObjectInitializer);

	//** Initialise **//
	virtual void Init();

	//** Load the Main Menu **//
	UFUNCTION(BlueprintCallable, Category = "Menu")
		void LoadMenu();

	//** Load the in game menu **//
	UFUNCTION(BlueprintCallable, Category = "Menu")
		void LoadInGameMenu();

	//** Join Server on given IP Address **//
	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

	//** Host the session **//
	UFUNCTION(Exec)
	virtual void Host() override;

	//** Loads the main menu from the in game menu **//
	virtual void LoadMainMenu() override;

	//** Debugger **//
	void DebugMessage(const FString& Message);

	/** WIDGET MENU **/
	TSubclassOf<UUserWidget> MenuClass;

	//** Main Menu widget **//
	class UMainMenu* Menu;

	/** WIDGET IN GAME MENU **/
	TSubclassOf<UUserWidget> InGameMenuClass;

	//** In game menu widget **//
	class UMenuWidget* InGameMenu;
	
};
