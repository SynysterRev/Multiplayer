// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RootGameUIPanel.h"

#include "UI/Target/TargetInfoWidget.h"
#include "UI/Widget/ResourceBarWidget.h"

void URootGameUIPanel::WidgetControllerSet_Implementation()
{
	check(TargetInfoWidget);
	TargetInfoWidget->SetWidgetController(WidgetController);
	
	check(HealthBarWidget);
	HealthBarWidget->SetWidgetController(WidgetController);
}
