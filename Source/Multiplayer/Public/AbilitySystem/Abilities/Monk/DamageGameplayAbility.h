// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "AbilitySystem/Data/BaseGameplayAbility.h"
#include "DamageGameplayAbility.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UDamageGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ExecuteAbilityLogic(const FGameplayAbilitySpecHandle Handle,
											 const FGameplayAbilityActorInfo* ActorInfo,
											 const FGameplayAbilityActivationInfo ActivationInfo,
											 const FGameplayEventData* TriggerEventData,
											 const FGameplayAbilityTargetDataHandle& TargetDataHandle) override;
	
public:
	
	// virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayCueTag;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> FXTest;
};
