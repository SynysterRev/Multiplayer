// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Data/BaseGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UDamageGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
public:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> Test;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cost")
	TSubclassOf<UGameplayEffect> GE_CostClass;
};
