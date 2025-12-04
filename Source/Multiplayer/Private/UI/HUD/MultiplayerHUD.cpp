// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MultiplayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/RootGameUIPanel.h"
#include "UI/WidgetController/GameRootUIWidgetController.h"

UGameRootUIWidgetController* AMultiplayerHUD::GetRootUIWidgetController(const FWidgetControllerParams& Params)
{
	if (!RootUIWidgetController)
	{
		RootUIWidgetController = NewObject<UGameRootUIWidgetController>(this, RootUIWidgetControllerClass);
		RootUIWidgetController->SetWidgetControllerParams(Params);
	}
	return RootUIWidgetController;
}

void AMultiplayerHUD::InitRootUI(APlayerController* InPC, UAbilitySystemComponent* InASC, APlayerState* InPS,
                                 UAttributeSet* InAS)
{
	if (RootGameUIWidgetClass)
	{
		RootGameUIPanel = CreateWidget<UMultiplayerCommonWidget>(
			GetWorld(), RootGameUIWidgetClass);

		if (RootGameUIPanel)
		{
			RootGameUIPanel->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Root Game UI class uninitialized"));
	}
	FWidgetControllerParams WidgetControllerParams(InPC, InASC, InPS, InAS);
	if (UMultiplayerWidgetController* WidgetController = GetRootUIWidgetController(WidgetControllerParams))
	{
		RootGameUIPanel->SetWidgetController(WidgetController);
	}
}
