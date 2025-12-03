// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "MultiplayerCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UAbilityInfo;

UCLASS(Abstract)
class MULTIPLAYER_API AMultiplayerCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMultiplayerCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return AttributesSet; }

protected:

	UPROPERTY(EditAnywhere, Category="Abilities")
	TMap<int32, UAbilityInfo*> StartingAbilities;

	UPROPERTY(BlueprintReadOnly, Category="Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	TObjectPtr<UAttributeSet> AttributesSet;
};
