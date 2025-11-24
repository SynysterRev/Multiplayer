// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilityCharacterBase.generated.h"

class UCharacterAbilitySystemComponent;
class UCharacterAttributeSet;
class UAbilityInfo;

UCLASS()
class MULTIPLAYER_API AAbilityCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterAbilitySystemComponent> CharacterAbilitySystemComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attributes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterAttributeSet> AttributesSet;

public:
	// Sets default values for this character's properties
	AAbilityCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category="Abilities")
	TMap<int32, UAbilityInfo*> StartingAbilities;

};
