// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MultiplayerHUD.generated.h"

class UMultiplayerAttributeSet;
class UAbilitySystemComponent;
class UGameRootUIWidgetController;
struct FWidgetControllerParams;
class UMultiplayerCommonWidget;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API AMultiplayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMultiplayerCommonWidget> RootGameUIPanel;

	UGameRootUIWidgetController* GetRootUIWidgetController(const FWidgetControllerParams& Params);
	void InitRootUI(APlayerController* InPC, UAbilitySystemComponent* InASC, APlayerState* InPS,
	                UMultiplayerAttributeSet* InAS);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMultiplayerCommonWidget> RootGameUIWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameRootUIWidgetController> RootUIWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UGameRootUIWidgetController> RootUIWidgetController;
};
