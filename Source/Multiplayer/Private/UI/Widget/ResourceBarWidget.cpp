// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ResourceBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UResourceBarWidget::UpdateResourceText(float CurrentValue, float MaxValue)
{
	if (ResourceText)
	{
		ResourceText->SetText(FText::FromString(FString::Printf(TEXT("%f / %f"), CurrentValue, MaxValue)));
	}
}

void UResourceBarWidget::UpdateResourceBar(float InPercent)
{
	if (ResourceBar)
	{
		ResourceBar->SetPercent(InPercent);
	}
}
