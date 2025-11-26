// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

class UGameplayAbility;

UCLASS(BlueprintType)
class MULTIPLAYER_API UAbilityInfo : public UDataAsset
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
	FScalableFloat Cooldown;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat ManaCost;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxCastDistance;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanSelfTarget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;
};