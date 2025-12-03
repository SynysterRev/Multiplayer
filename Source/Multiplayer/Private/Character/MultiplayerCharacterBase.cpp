// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MultiplayerCharacterBase.h"

// Sets default values
AMultiplayerCharacterBase::AMultiplayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AMultiplayerCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
