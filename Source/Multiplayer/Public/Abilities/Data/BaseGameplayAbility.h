// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInfo.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

class AMultiplayerPlayerController;
class AMultiplayerCharacter;
class UTargetingComponent;
class UAbilityInfo;

DECLARE_LOG_CATEGORY_EXTERN(LogGameplayAbility, Log, All);

UCLASS()
class MULTIPLAYER_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY()
	FGameplayAbilityTargetDataHandle CachedTargetData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cooldown")
	FGameplayTagContainer CooldownTags;

	// Temp container that we will return the pointer to in GetCooldownTags().
	// This will be a union of our CooldownTags and the Cooldown GE's cooldown tags.
	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags;
	
	UPROPERTY(EditDefaultsOnly, Category="AbilityInfo")
	TObjectPtr<UAbilityInfo> AbilityInfo;
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	TObjectPtr<UAnimMontage> CastAnim;
	
	virtual void ExecuteAbilityLogic(const FGameplayAbilitySpecHandle Handle,
											 const FGameplayAbilityActorInfo* ActorInfo,
											 const FGameplayAbilityActivationInfo ActivationInfo,
											 const FGameplayEventData* TriggerEventData,
											 const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	void OnCompleted();
	
	UFUNCTION()
	void OnCancelled();
	
	UFUNCTION()
	void OnInterrupted();
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	UTargetingComponent* GetTargetingComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	AMultiplayerCharacter* GetMultiplayerCharacterFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	AController* GetControllerFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category="Ability")
	AMultiplayerPlayerController* GetMultiplayerControllerFromActorInfo() const;
	
public:
	
	virtual const FGameplayTagContainer* GetCooldownTags() const override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	FScalableFloat GetCost() const { return AbilityInfo ? AbilityInfo->ManaCost : 0.0f; };
};
