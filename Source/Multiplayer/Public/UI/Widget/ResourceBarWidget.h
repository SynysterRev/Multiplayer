// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MultiplayerCommonWidget.h"
#include "ResourceBarWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UResourceBarWidget : public UMultiplayerCommonWidget
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ResourceBar;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ResourceText;
	
	UPROPERTY(BlueprintReadWrite)
	float CurrentResource;
	
	UPROPERTY(BlueprintReadWrite)
	float MaxResource;
	
	UFUNCTION(BlueprintCallable)
	void UpdateResourceText(float CurrentValue);
	
	UFUNCTION(BlueprintCallable)
	void UpdateResourceBar(float InPercent);
};
