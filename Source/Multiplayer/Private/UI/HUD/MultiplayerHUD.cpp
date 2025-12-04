// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MultiplayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/RootGameUIPanel.h"

void AMultiplayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (RootGameUIWidgetClass)
	{
		RootGameUIPanel = CreateWidget<UMultiplayerCommonWidget>(
			GetWorld(), RootGameUIWidgetClass);
		
		if (RootGameUIPanel)
		{
			RootGameUIPanel->AddToViewport();
		}
	}
}
