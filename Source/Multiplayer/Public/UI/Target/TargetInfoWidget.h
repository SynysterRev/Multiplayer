// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTextBlock.h"
#include "UI/Widget/MultiplayerCommonWidget.h"
#include "TargetInfoWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UTargetInfoWidget : public UMultiplayerCommonWidget
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> TargetHealthBar;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> TargetName;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void UpdateTarget(AActor* NewTarget);
	
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);
	void UpdateTargetName(const FText& NewName);
};
