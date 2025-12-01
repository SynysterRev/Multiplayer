// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Data/BaseGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MultiplayerPlayerController.h"
#include "Abilities/Data/AbilityInfo.h"
#include "Characters/MultiplayerCharacter.h"
#include "Characters/Components/TargetingComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

DEFINE_LOG_CATEGORY(LogGameplayAbility);

void UBaseGameplayAbility::ExecuteAbilityLogic(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData,
                                               const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
}

void UBaseGameplayAbility::OnCompleted()
{
	if (!HasAuthority(&CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
		return;
	}
	ExecuteAbilityLogic(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, &CurrentEventData,
	                    CachedTargetData);
}

void UBaseGameplayAbility::OnCancelled()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] OnCancelled called - HasAuthority: %s"),
	       *CurrentActorInfo->AvatarActor->GetName(),
	       HasAuthority(&CurrentActivationInfo) ? TEXT("YES") : TEXT("NO"));
}

void UBaseGameplayAbility::OnInterrupted()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] OnInterrupted called - HasAuthority: %s"),
	       *CurrentActorInfo->AvatarActor->GetName(),
	       HasAuthority(&CurrentActivationInfo) ? TEXT("YES") : TEXT("NO"));
}

UTargetingComponent* UBaseGameplayAbility::GetTargetingComponentFromActorInfo() const
{
	AMultiplayerCharacter* Character = GetMultiplayerCharacterFromActorInfo();
	return Character ? Character->GetTargetingComponent() : nullptr;
}

AMultiplayerCharacter* UBaseGameplayAbility::GetMultiplayerCharacterFromActorInfo() const
{
	return CurrentActorInfo ? Cast<AMultiplayerCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr;
}

AController* UBaseGameplayAbility::GetControllerFromActorInfo() const
{
	if (CurrentActorInfo)
	{
		if (APlayerController* PC = CurrentActorInfo->PlayerController.Get())
		{
			return PC;
		}
		if (AMultiplayerCharacter* Character = GetMultiplayerCharacterFromActorInfo())
		{
			return Character->GetController();
		}
	}
	return nullptr;
}

AMultiplayerPlayerController* UBaseGameplayAbility::GetMultiplayerControllerFromActorInfo() const
{
	return CurrentActorInfo ? Cast<AMultiplayerPlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr;
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
	AMultiplayerCharacter* AvatarActor = GetMultiplayerCharacterFromActorInfo();
	UTargetingComponent* TargetingComp = GetTargetingComponentFromActorInfo();
	if (!AbilityInfo)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("No ability info specified for ability '%s'"), *GetName());
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
		return;
	}

	if (TargetingComp)
	{
		// will need improvement to check enemy/ally
		AActor* TargetActor = TargetingComp->GetCurrentTarget()
			                      ? TargetingComp->GetCurrentTarget()
			                      : AbilityInfo->bCanSelfTarget
			                      ? AvatarActor
			                      : nullptr;

		if (!TargetActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("No targeted actor"));
			EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
			return;
		}

		float MaxDistanceSquared = AbilityInfo->MaxCastDistance * AbilityInfo->MaxCastDistance;
		if (FVector::DistSquared(TargetActor->GetActorLocation(), AvatarActor->GetActorLocation()) > MaxDistanceSquared)
		{
			UE_LOG(LogTemp, Warning, TEXT("Too far away"));
			EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
			return;
		}
		const FGameplayAbilityTargetDataHandle TargetDataHandle =
			UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(TargetActor);

		CachedTargetData = TargetDataHandle;

		UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, TEXT("CastAnim"), CastAnim);
		Task->OnCompleted.AddDynamic(this, &UBaseGameplayAbility::OnCompleted);
		Task->OnInterrupted.AddDynamic(this, &UBaseGameplayAbility::OnInterrupted);
		Task->OnCancelled.AddDynamic(this, &UBaseGameplayAbility::OnCancelled);

		Task->ReadyForActivation();
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	}
}
