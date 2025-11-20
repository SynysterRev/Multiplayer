// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Professions/Data/BaseGameplayAbility.h"
#include "HealGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UHealGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UGameplayEffect> Test;
};
