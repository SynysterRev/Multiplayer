// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerPlayerController.generated.h"

class URootGameUIPanel;
class AMultiplayerCharacter;
class UPathFollowingComponent;
class UInputAction;
class UInputMappingContext;
class UUserWidget;
class UNiagaraSystem;


#define ECC_Interactable ECC_GameTraceChannel2
#define ECC_Ground ECC_GameTraceChannel3

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerPlayerController, Log, All);

UCLASS(abstract)
class AMultiplayerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UNiagaraSystem* FXCursor;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LeftClickAction;
	
	UPROPERTY(Transient)
	TObjectPtr<AMultiplayerCharacter> MultiplayerCharacter;
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<URootGameUIPanel> RootGameUIPanelClass;
	
	UPROPERTY(Transient, BlueprintReadOnly, Category="UI")
	TObjectPtr<URootGameUIPanel> RootGameUIPanel;
	
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void OnClick();
	
	UFUNCTION(Server, Reliable)
	void ServerMoveToLocation(const FVector& TargetLocation);
	
	void MoveToLocation(const FVector& TargetLocation);
	
public:
	AMultiplayerPlayerController();
	
	AMultiplayerCharacter* GetMultiplayerCharacter() const;
};
