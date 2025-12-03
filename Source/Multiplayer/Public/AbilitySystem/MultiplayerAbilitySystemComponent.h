// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MultiplayerAbilitySystemComponent.generated.h"

class UAbilityInfo;

USTRUCT(BlueprintType)
struct FEquippedAbility
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilityInfo> AbilityInfo = nullptr;
};

UCLASS()
class MULTIPLAYER_API UMultiplayerAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Abilities|CharacterAbilities")
	TMap<int32, FEquippedAbility> EquippedAbilities;
	
	void AddAbility(int32 SlotIndex, UAbilityInfo* AbilityInfo);
	
public:
	UFUNCTION(BlueprintCallable, Category="Abilities|CharacterAbilities")
	void InitializeAbilities(const TMap<int32, UAbilityInfo*>& StartingAbilities);
	
	UFUNCTION(BlueprintCallable, Category="Abilities|CharacterAbilities")
	bool ActivateAbility(int32 SlotIndex);
};
