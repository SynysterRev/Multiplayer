// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AbilityCharacterBase.h"

#include "Characters/Components/CharacterAbilitySystemComponent.h"
#include "Characters/Player/Data/CharacterAttributeSet.h"

// Sets default values
AAbilityCharacterBase::AAbilityCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CharacterAbilitySystemComp = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AttributesSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("AttributesSet"));
}

// Called when the game starts or when spawned
void AAbilityCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	CharacterAbilitySystemComp->InitAbilityActorInfo(this, this);
	CharacterAbilitySystemComp->InitializeAbilities(StartingAbilities);
}

UAbilitySystemComponent* AAbilityCharacterBase::GetAbilitySystemComponent() const
{
	return CharacterAbilitySystemComp;
}
