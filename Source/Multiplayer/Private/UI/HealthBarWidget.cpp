// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"

#include "AbilitySystem/MultiplayerAttributeSet.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetAttributeSet(UMultiplayerAttributeSet* AttributeSet)
{
	AttributeSet->OnHealthChanged.AddDynamic(this, &UHealthBarWidget::OnHealthChanged);
}

void UHealthBarWidget::OnHealthChanged(UMultiplayerAttributeSet* AttributeSet, float OldValue, float NewValue)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewValue / AttributeSet->GetMaxHealth());
	}
}
