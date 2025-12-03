// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MultiplayerEnemyCharacter.h"

#include "AbilitySystem/MultiplayerAbilitySystemComponent.h"
#include "AbilitySystem/MultiplayerAttributeSet.h"

AMultiplayerEnemyCharacter::AMultiplayerEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMultiplayerAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributesSet = CreateDefaultSubobject<UMultiplayerAttributeSet>("AttributeSet");
}

void AMultiplayerEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
