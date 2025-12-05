// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MultiplayerCommonWidget.h"
#include "RootGameUIPanel.generated.h"

class UResourceBarWidget;
class UTargetInfoWidget;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API URootGameUIPanel : public UMultiplayerCommonWidget
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTargetInfoWidget> TargetInfoWidget;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UResourceBarWidget> HealthBarWidget;

	virtual void WidgetControllerSet_Implementation() override;
};
