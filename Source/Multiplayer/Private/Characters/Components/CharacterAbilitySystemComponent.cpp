// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/CharacterAbilitySystemComponent.h"

#include "Abilities/Data/AbilityInfo.h"

void UCharacterAbilitySystemComponent::AddAbility(int32 SlotIndex, UAbilityInfo* AbilityInfo)
{
	if (GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Give ability '%s, %d'"), *GetOwner()->GetName(), SlotIndex);
		FGameplayAbilitySpec AbilitySpec(AbilityInfo->AbilityClass, 1, SlotIndex, this);
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityInfo->AbilityTag);
		GiveAbility(AbilitySpec);
	}

	FEquippedAbility EquippedAbility;
	EquippedAbility.AbilityInfo = AbilityInfo;
	EquippedAbilities.Add(SlotIndex, EquippedAbility);
}

void UCharacterAbilitySystemComponent::InitializeAbilities(const TMap<int32, UAbilityInfo*>& StartingAbilities)
{
	for (const auto& [SlotIndex, AbilityInfo] : StartingAbilities)
	{
		AddAbility(SlotIndex, AbilityInfo);
	}
}

bool UCharacterAbilitySystemComponent::ActivateAbility(int32 SlotIndex)
{
	if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromInputID(SlotIndex))
	{
		return TryActivateAbility(Spec->Handle);
	}
	return false;
}
