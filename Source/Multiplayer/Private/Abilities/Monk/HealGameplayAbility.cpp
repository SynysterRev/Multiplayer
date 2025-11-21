// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Monk/HealGameplayAbility.h"

#include "AbilitySystemComponent.h"

void UHealGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
	
	if (!AbilitySystemComponent)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	if (HasAuthority(&ActivationInfo))
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(Test, 1, AbilitySystemComponent->MakeEffectContext());
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}
