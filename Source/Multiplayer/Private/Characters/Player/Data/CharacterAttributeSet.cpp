// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Data/CharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	InitMana(25.0f);
	InitMaxMana(25.0f);
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
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

void UCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Health, OldValue);
	const float OldHealth = OldValue.GetCurrentValue();
	const float NewHealth = GetHealth();
	UE_LOG(LogTemp, Warning, TEXT("PostChange: Attribute changed %.2f -> %.2f"), OldHealth, NewHealth);
	OnHealthChanged.Broadcast(this, OldHealth, NewHealth);
}

void UCharacterAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Mana, OldValue);
	const float OldMana = OldValue.GetCurrentValue();
	const float NewMana = GetMana();
	UE_LOG(LogTemp, Warning, TEXT("PostChange: Attribute changed %.2f -> %.2f"), OldMana, NewMana);
	OnManaChanged.Broadcast(this, OldMana, NewMana);
}

void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterAttributeSet, Health);
	DOREPLIFETIME(UCharacterAttributeSet, MaxHealth);
	DOREPLIFETIME(UCharacterAttributeSet, Mana);
	DOREPLIFETIME(UCharacterAttributeSet, MaxMana);
}
