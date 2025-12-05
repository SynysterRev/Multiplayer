// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ResourceBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UResourceBarWidget::UpdateResourceText(float CurrentValue)
{
	if (ResourceText)
	{
		ResourceText->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::TruncToInt(CurrentValue))));
	}
}

void UResourceBarWidget::UpdateResourceBar(float InPercent)
{
	if (ResourceBar)
	{
		ResourceBar->SetPercent(InPercent);
	}
}
