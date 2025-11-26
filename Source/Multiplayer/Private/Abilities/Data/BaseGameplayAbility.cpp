// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Data/BaseGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Data/AbilityInfo.h"
#include "Characters/MultiplayerCharacter.h"
#include "Characters/Components/TargetingComponent.h"

DEFINE_LOG_CATEGORY(LogGameplayAbility);

void UBaseGameplayAbility::ExecuteAbilityLogic(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData,
                                               const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
}

const FGameplayTagContainer* UBaseGameplayAbility::GetCooldownTags() const
{
	FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
	MutableTags->Reset();
	// MutableTags writes to the TempCooldownTags on the CDO so clear it in case the ability cooldown tags change (moved to a different slot)
	if (const FGameplayTagContainer* ParentTags = Super::GetCooldownTags())
	{
		MutableTags->AppendTags(*ParentTags);
	}
	MutableTags->AppendTags(CooldownTags);
	return MutableTags;
}

void UBaseGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo) const
{
	if (!AbilityInfo)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("No ability info specified for ability '%s'"), *GetName());
		return;
	}
	if (UGameplayEffect* CooldownGE = GetCooldownGameplayEffect())
	{
		FGameplayEffectSpecHandle SpecHandle =
			MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTags);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Abilities.Cooldown")),
		                                               AbilityInfo->Cooldown.GetValueAtLevel(GetAbilityLevel()));
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}

void UBaseGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo,
                                           const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	if (!HasAuthority(&ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	AMultiplayerCharacter* AvatarActor = Cast<AMultiplayerCharacter>(ActorInfo->AvatarActor.Get());
	UTargetingComponent* TargetingComp = AvatarActor
		                                     ? AvatarActor->GetTargetingComponent()
		                                     : nullptr;
	if (!AbilityInfo)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("No ability info specified for ability '%s'"), *GetName());
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}
	// 3. 🌟 Récupérer la cible directement depuis le Component
	if (TargetingComp)
	{
		AActor* TargetActor = TargetingComp->GetCurrentTarget()
			                      ? TargetingComp->GetCurrentTarget()
			                      : AbilityInfo->bCanSelfTarget
			                      ? AvatarActor
			                      : nullptr;

		if (!TargetActor)
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
			return;
		}
		const FGameplayAbilityTargetDataHandle TargetDataHandle =
			UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(TargetActor);
		// 4. Si la cible est valide, lancer la logique de l'Ability
		ExecuteAbilityLogic(Handle, ActorInfo, ActivationInfo, TriggerEventData, TargetDataHandle);

		// 5. Terminer l'Ability (avec succès)
		// EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
	else
	{
		// Pas de cible trouvée (l'Ability n'est pas lancée)
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	}
}
