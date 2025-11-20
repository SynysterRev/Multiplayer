// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Data/AbilityCostMMC.h"

#include "Abilities/Data/BaseGameplayAbility.h"

float UAbilityCostMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UBaseGameplayAbility* Ability = Cast<UBaseGameplayAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (!Ability)
	{
		return 0.0f;
	}

	return Ability->Cost.GetValueAtLevel(Ability->GetAbilityLevel());
}
