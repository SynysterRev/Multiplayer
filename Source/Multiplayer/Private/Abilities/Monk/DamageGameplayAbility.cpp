// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Monk/DamageGameplayAbility.h"

#include "AbilitySystemComponent.h"

void UDamageGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo,
                                             const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!HasAuthority(&ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(GE_CostClass);
	// if (CostSpecHandle.IsValid())
	// {
	// 	FGameplayTag CostTag = FGameplayTag::RequestGameplayTag(FName(("Abilities.Cost.Mana")));
	// 	CostSpecHandle.Data.Get()->SetByCallerTagMagnitudes.Add(CostTag, -15.0f);
	// }

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		const UGameplayEffect* GameplayEffect = Test->GetDefaultObject<UGameplayEffect>();
		ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GameplayEffect, 1);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}
