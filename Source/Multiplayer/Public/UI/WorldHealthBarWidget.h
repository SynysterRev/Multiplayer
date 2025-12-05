// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldHealthBarWidget.generated.h"

class UMultiplayerAttributeSet;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UWorldHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	void InitHealthBarWidget(UMultiplayerAttributeSet* AttributeSet);
	
protected:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> HealthBarText;
	
	UFUNCTION()
	void OnHealthChanged(UMultiplayerAttributeSet* AttributeSet, float OldValue, float NewValue);
	
	void UpdateHealthBar(const UMultiplayerAttributeSet* AttributeSet) const;
};
