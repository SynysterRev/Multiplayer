// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Professions/Data/BaseGameplayAbility.h"
#include "ProfessionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UProfessionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Profession")
	FName ProfessionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Profession")
	TObjectPtr<UTexture2D> ProfessionIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Profession")
	FText ProfessionDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Profession")
	TArray<UBaseGameplayAbility*> ProfessionAbilities;
};
