// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MultiplayerWidgetController.generated.h"

class UMultiplayerAttributeSet;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams()
	{
	}

	FWidgetControllerParams(APlayerController* InPC, UAbilitySystemComponent* InASC, APlayerState* InPS,
	                        UMultiplayerAttributeSet* InAS) : PlayerController(InPC), AbilitySystemComponent(InASC),
	                                               PlayerState(InPS), AttributeSet(InAS)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<UMultiplayerAttributeSet> AttributeSet = nullptr;
};


UCLASS()
class MULTIPLAYER_API UMultiplayerWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);
	
	virtual void BroadcastInitialValues();

protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UMultiplayerAttributeSet> AttributeSet;
};
