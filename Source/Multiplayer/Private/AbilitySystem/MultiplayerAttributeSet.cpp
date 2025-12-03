// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MultiplayerAttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UMultiplayerAttributeSet::UMultiplayerAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	InitMana(25.0f);
	InitMaxMana(25.0f);
}

void UMultiplayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0,GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0,GetMaxMana());
	}
	Super::PreAttributeChange(Attribute, NewValue);
}

void UMultiplayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& EffectData)
{
	Super::PostGameplayEffectExecute(EffectData);
	if (EffectData.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Convert into -Health and then clamp
		const float DamageValue = GetDamage();
		const float OldHealthValue = GetHealth();
		const float MaxHealthValue = GetMaxHealth();
		const float NewHealthValue = FMath::Clamp(OldHealthValue - DamageValue, 0.0f, MaxHealthValue);
	 
		if (OldHealthValue != NewHealthValue)
		{
			// Set the new health after clamping to min-max
			SetHealth(NewHealthValue);
		}
	}
	
	SetDamage(0.0f);
}

void UMultiplayerAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMultiplayerAttributeSet, Health, OldValue);
	const float OldHealth = OldValue.GetCurrentValue();
	const float NewHealth = GetHealth();
	OnHealthChanged.Broadcast(this, OldHealth, NewHealth);
}

void UMultiplayerAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMultiplayerAttributeSet, MaxHealth, OldValue);
	const float OldMaxHealth = OldValue.GetCurrentValue();
	const float NewMaxHealth = GetMaxHealth();
	OnHealthChanged.Broadcast(this, OldMaxHealth, NewMaxHealth);
}

void UMultiplayerAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMultiplayerAttributeSet, Mana, OldValue);
	const float OldMana = OldValue.GetCurrentValue();
	const float NewMana = GetMana();
	OnManaChanged.Broadcast(this, OldMana, NewMana);
}

void UMultiplayerAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMultiplayerAttributeSet, MaxMana, OldValue);
	const float OldMaxMana = OldValue.GetCurrentValue();
	const float NewMaxMana = GetMaxHealth();
	OnHealthChanged.Broadcast(this, OldMaxMana, NewMaxMana);
}

void UMultiplayerAttributeSet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMultiplayerAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMultiplayerAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMultiplayerAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMultiplayerAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}
