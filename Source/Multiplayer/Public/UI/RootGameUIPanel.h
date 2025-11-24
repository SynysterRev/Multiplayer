// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "RootGameUIPanel.generated.h"

class UTargetInfoWidget;
/**
 * 
 */
UCLASS()
class MULTIPLAYER_API URootGameUIPanel : public UCommonUserWidget
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTargetInfoWidget> TargetInfoWidget;
	
};
