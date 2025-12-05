// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/GameRootUIWidgetController.h"

#include "AbilitySystem/MultiplayerAttributeSet.h"

void UGameRootUIWidgetController::BroadcastInitialValues()
{
	check(AttributeSet);
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
}
