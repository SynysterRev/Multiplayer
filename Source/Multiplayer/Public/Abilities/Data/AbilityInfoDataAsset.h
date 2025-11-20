// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfoDataAsset.generated.h"

UCLASS(BlueprintType)
class MULTIPLAYER_API UAbilityInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AbilityName;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Cooldown;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ManaCost;
};