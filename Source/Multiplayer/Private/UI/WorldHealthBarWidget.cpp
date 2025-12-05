// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WorldHealthBarWidget.h"

#include "AbilitySystem/MultiplayerAttributeSet.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWorldHealthBarWidget::InitHealthBarWidget(UMultiplayerAttributeSet* AttributeSet)
{
	AttributeSet->OnHealthChanged.AddDynamic(this, &UWorldHealthBarWidget::OnHealthChanged);
	UpdateHealthBar(AttributeSet);
}

void UWorldHealthBarWidget::OnHealthChanged(UMultiplayerAttributeSet* AttributeSet, float OldValue, float NewValue)
{
	UpdateHealthBar(AttributeSet);
}

void UWorldHealthBarWidget::UpdateHealthBar(const UMultiplayerAttributeSet* AttributeSet) const
{
	if (HealthBar)
	{
		float percent = AttributeSet->GetMaxHealth() > 0.f ? AttributeSet->GetHealth() / AttributeSet->GetMaxHealth() : 0.f;
		HealthBar->SetPercent(percent);
	}
	if (HealthBarText)
	{
		HealthBarText->SetText(
			FText::FromString(
				FString::Printf(TEXT("%d / %d"), static_cast<int32>(AttributeSet->GetHealth()),
				                static_cast<int32>(AttributeSet->GetMaxHealth()))));
	}
}
