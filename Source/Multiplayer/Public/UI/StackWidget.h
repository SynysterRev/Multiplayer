// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "StackWidget.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_API UStackWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Stack = nullptr;

public:

	void PushWidget(UCommonActivatableWidget* ActivatableWidget) const;
	void PopWidget(UCommonActivatableWidget* ActivatableWidget) const;
	void PopLastWidget() const;
	void PopAllWidget() const;
	
};
