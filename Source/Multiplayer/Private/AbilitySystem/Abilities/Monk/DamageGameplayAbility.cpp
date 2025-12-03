// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Monk/DamageGameplayAbility.h"
#include "AbilitySystem/MultiplayerAbilitySystemComponent.h"

void UDamageGameplayAbility::ExecuteAbilityLogic(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData,
                                                 const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	// Super::ExecuteAbilityLogic(TargetedActor);
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, TargetDataHandle, DamageEffect, 1);
		if (GetAbilitySystemFromActorInfo())
		{
			FGameplayCueParameters CueParams;
			CueParams.SourceObject = GetAvatarActorFromActorInfo();

			// Récupérer la target depuis le TargetDataHandle
			if (TargetDataHandle.IsValid(0))
			{
				const FGameplayAbilityTargetData* Data = TargetDataHandle.Get(0);
				if (Data)
				{
					TArray<TWeakObjectPtr<AActor>> TargetActors = Data->GetActors();
					if (TargetActors.Num() > 0 && TargetActors[0].IsValid())
					{
						AActor* TargetActor = TargetActors[0].Get();
						CueParams.TargetAttachComponent = TargetActor->GetRootComponent();
						CueParams.Location = TargetActor->GetActorLocation();
						CueParams.SourceObject = FXTest;
					}
				}
			}
			GetAbilitySystemFromActorInfo()->ExecuteGameplayCue(GameplayCueTag, CueParams);
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		}
		else
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}
	}
}

// void UDamageGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
//                                              const FGameplayAbilityActorInfo* ActorInfo,
//                                              const FGameplayAbilityActivationInfo ActivationInfo,
//                                              const FGameplayEventData* TriggerEventData)
// {
// 	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
//
// 	if (!HasAuthority(&ActivationInfo))
// 	{
// 		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
// 		return;
// 	}
// 	// FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(GE_CostClass);
// 	// if (CostSpecHandle.IsValid())
// 	// {
// 	// 	FGameplayTag CostTag = FGameplayTag::RequestGameplayTag(FName(("Abilities.Cost.Mana")));
// 	// 	CostSpecHandle.Data.Get()->SetByCallerTagMagnitudes.Add(CostTag, -15.0f);
// 	// }
// 	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
// 	{
// 		const UGameplayEffect* GameplayEffect = Test->GetDefaultObject<UGameplayEffect>();
// 		ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GameplayEffect, 1);
// 		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
// 	}
// 	else
// 	{
// 		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
// 	}
// }
