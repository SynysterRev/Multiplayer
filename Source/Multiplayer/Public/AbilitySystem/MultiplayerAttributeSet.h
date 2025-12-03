// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MultiplayerAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedEvent, UMultiplayerAttributeSet*, AttributeSet, float, OldValue, float, NewValue);

UCLASS()
class MULTIPLAYER_API UMultiplayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UMultiplayerAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData Damage;
	
	// allow to modify the new value of the attribute before it's available to other systems
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& EffectData) override;
	
	//call when the server changes a value
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnManaChanged;
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnMaxManaChanged;

	ATTRIBUTE_ACCESSORS_BASIC(UMultiplayerAttributeSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UMultiplayerAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS_BASIC(UMultiplayerAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS_BASIC(UMultiplayerAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS_BASIC(UMultiplayerAttributeSet, Damage);
};
