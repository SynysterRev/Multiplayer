// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MultiplayerCommonWidget.h"

void UMultiplayerCommonWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

void UMultiplayerCommonWidget::WidgetControllerSet_Implementation()
{
}
