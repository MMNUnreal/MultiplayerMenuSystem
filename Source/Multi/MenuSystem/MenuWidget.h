// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTI_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//** Adds widget to viewport & sets up input**//
	void Setup();

	//** Removes widget from viewport and changes input **//
	void Teardown();

	//** Sets menu interface for widget **//
	void SetMenuInterface(IMenuInterface* MenuInterfaceIn);

protected:
	IMenuInterface* MenuInterface;
	
};
