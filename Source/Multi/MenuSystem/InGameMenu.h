// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"

#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class MULTI_API UInGameMenu : public UMenuWidget
{

	GENERATED_BODY()

protected:
	//** Initialise **//
	virtual bool Initialize() override;

	//** On Cancel Button pressed - return to game *//
	UFUNCTION()
	void Cancel();

	//** On Quit button pressed - return to main menu and quit game **//
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void Quit();

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

};
