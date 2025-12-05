// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MultiplayerWidgetController.h"
#include "GameRootUIWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, NewMaxHealth);

UCLASS(Blueprintable, BlueprintType)
class MULTIPLAYER_API UGameRootUIWidgetController : public UMultiplayerWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChanged OnMaxHealthChanged;
};
