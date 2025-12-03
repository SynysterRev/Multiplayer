// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MultiplayerPlayerState.h"

#include "AbilitySystem/MultiplayerAbilitySystemComponent.h"
#include "AbilitySystem/MultiplayerAttributeSet.h"

AMultiplayerPlayerState::AMultiplayerPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMultiplayerAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributesSet = CreateDefaultSubobject<UMultiplayerAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AMultiplayerPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
