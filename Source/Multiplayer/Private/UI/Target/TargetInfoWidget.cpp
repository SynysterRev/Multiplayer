// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Target/TargetInfoWidget.h"

#include "Character/MultiplayerCharacter.h"
#include "Character/Components/TargetingComponent.h"
#include "Components/ProgressBar.h"
#include "Player/MultiplayerPlayerController.h"

class AMultiplayerPlayerController;

void UTargetInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (AMultiplayerPlayerController* PC = Cast<AMultiplayerPlayerController>(GetOwningPlayer()))
	{
		AMultiplayerCharacter* Character = PC->GetMultiplayerCharacter();
		if (!Character)
		{
			return;
		}
		UTargetingComponent* TargetingComponent = Character->GetTargetingComponent();
		if (!TargetingComponent)
		{
			return;
		}
		TargetingComponent->OnTargetChanged.AddDynamic(this, &UTargetInfoWidget::UpdateTarget);
	}
	SetVisibility(ESlateVisibility::Collapsed);
}

void UTargetInfoWidget::UpdateTarget(AActor* NewTarget)
{
	if (!NewTarget)
	{
		//remove widget
		SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	else if (GetVisibility() == ESlateVisibility::Collapsed)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	UpdateTargetName(FText::FromString(NewTarget->GetName()));
}

void UTargetInfoWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (!TargetHealthBar)
	{
		return;
	}
	
	TargetHealthBar->SetPercent(CurrentHealth / MaxHealth);
}

void UTargetInfoWidget::UpdateTargetName(const FText& NewName)
{
	if (!TargetName)
	{
		return;
	}
	TargetName->SetText(NewName);
}
